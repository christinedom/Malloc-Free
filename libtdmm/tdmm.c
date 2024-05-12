
#include "tdmm.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>

// do the cases go in main or tmalloc method
#define MEMORY (1024 * 1024 * 64)
#define ALIGN(size, align) (((size) + (align - 1)) & ~(align - 1))

alloc_strat_e strategy;

// represents a memory block
typedef struct block
{
  size_t size;
  int free;
  struct block *next;
  struct block *previous;
} memoryBlock;

static char *memory = NULL;
static memoryBlock *head = NULL;
static memoryBlock *stack = NULL;

memoryBlock *firstFitMethod(size_t alignedSize, memoryBlock **current, memoryBlock **prev)
{
  while ((*current) != NULL)
  {
    if ((*current)->free && (*current)->size >= alignedSize)
    {
      return *current;
    }
    *prev = *current;
    *current = (*current)->next;
  }
  return NULL;
}

void *
worstFitMethod (size_t alignedSize, memoryBlock **current, memoryBlock **prev)
{
  memoryBlock *bestFit = NULL;
  size_t maxSize = 0;
  while (*current != NULL)
    {
      if ((*current)->free && (*current)->size >= alignedSize)
        {
          if ((*current)->size > maxSize)
            {
              maxSize = (*current)->size;
              bestFit = *current;
            }
        }
      *prev = *current;
      *current = (*current)->next;
    }
  if (bestFit != NULL)
    {
      bestFit->free = 0;
      return bestFit;
    }
  return NULL;
}
void *
bestFitMethod (size_t alignedSize, memoryBlock **current, memoryBlock **prev)
{
  memoryBlock *bestFit = NULL;
  size_t minSize = MEMORY;

  while (*current != NULL)
    {
      if ((*current)->free && (*current)->size >= alignedSize)
        {
          if ((*current)->size < minSize)
            {
              minSize = (*current)->size;
              bestFit = *current;
            }
        }
      *prev = *current;
      *current = (*current)->next;
    }
  if (bestFit != NULL)
    {
      bestFit->free = 0;
      return bestFit;
    }
  return NULL;
}

memoryBlock *
splitBlock (memoryBlock *block, size_t size)
{
  if (block->size < size * 2 + sizeof (memoryBlock))
    {
      return NULL;
    }
  memoryBlock *buddy
      = (memoryBlock *)((char *)block + size + sizeof (memoryBlock));
  buddy->size = block->size - size - sizeof (memoryBlock);
  buddy->free = 1;
  buddy->next = block->next;
  buddy->previous = block;
  block->size = size;
  block->next = buddy;

  if (buddy->next != NULL)
    {
      buddy->next->previous = buddy;
    }
  return buddy;
}
void *
buddyAllocationMethod (size_t alignedSize)
{
  size_t blockSize = MEMORY;
  memoryBlock *current = head;
  while (current != NULL)
    {
      if (current->free && current->size >= alignedSize)
        {
          while (current->size >= alignedSize * 2 + sizeof (memoryBlock))
            {
              memoryBlock *buddy = splitBlock (current, alignedSize);
              if (buddy != NULL)
                {
                  buddy->free = 0;
                  return buddy;
                }
              current = current->next;
            }
          current->free = 0;
          return current;
        }
      current = current->next;
    }
  return NULL;
}

// helper method for garbage collect!
void
scanForPointers(void *start, void *end, bool *in_use)
{
    char *ptr = (char *)start;
    while (ptr < (char *)end)
    {
        memoryBlock *block = (memoryBlock *)((char *)ptr - sizeof(memoryBlock));
        if (block >= head && block < (memoryBlock *)((char *)head + MEMORY))
        {
            if (!block->free)
            {
                *in_use = true;
                return;
            }
        }
        ptr += sizeof(void *);
    }
    *in_use = false;
}

void
t_init (alloc_strat_e strat, void *stack_bot)
{
  strategy = strat;
  head = NULL;
  memory = (char *)mmap (NULL, MEMORY, PROT_READ | PROT_WRITE,
                         MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

void *
t_malloc (size_t size)
{
  
  // Align the requested size to the nearest multiple of 4
  size_t alignedSize = ALIGN (size, 4);
  // Calculate the total size required, including space for the memoryBlock
  size_t totalSize = alignedSize + sizeof (memoryBlock);
  // Align the total size to the nearest multiple of the system page size
  size_t allocSize = ALIGN (totalSize, sysconf (_SC_PAGESIZE));

  if (allocSize > MEMORY)
    {
      return NULL;
    }

  // Starting to traverse through linked list
  memoryBlock *current = head;
  memoryBlock *prev = NULL;
  memoryBlock *bestFit = NULL;

  if (strategy == FIRST_FIT)
    {
      bestFit = firstFitMethod (alignedSize, &current, &prev);
    }
  else if (strategy == BEST_FIT)
    {
      bestFit = bestFitMethod (alignedSize, &current, &prev);
    }
  else if (strategy == WORST_FIT)
    {
      bestFit = worstFitMethod (alignedSize, &current, &prev);
    }
  else if (strategy == BUDDY)
    {
      bestFit = buddyAllocationMethod (alignedSize);
    }
  else
    {
      return NULL;
    }

  if (bestFit == NULL)
    {
      bestFit = (memoryBlock *)mmap (NULL, MEMORY, PROT_READ | PROT_WRITE,
                                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
      if (bestFit == MAP_FAILED)
        {
          return NULL;
        }
      bestFit->size = MEMORY;
      bestFit->free = 0;
      bestFit->next = NULL;
      bestFit->previous = NULL;
      head = bestFit;
      return (void *)((char *)bestFit + sizeof (memoryBlock));
    }
  else
    {
      size_t remainingSize = bestFit->size - totalSize;
      if (remainingSize >= sizeof (memoryBlock))
        {
          memoryBlock *newBlock = (memoryBlock *)((char *)bestFit + totalSize);
          newBlock->size = remainingSize - sizeof (memoryBlock);
          newBlock->free = 1;
          newBlock->next = bestFit->next;
          newBlock->previous = bestFit;
          bestFit->next = newBlock;
          if (newBlock->next != NULL)
            {
              newBlock->next->previous = newBlock;
            }
          bestFit->size = totalSize;
        }
      if (bestFit == head)
        {
          head = bestFit->next;
        }
      bestFit->free = 0;
      return (void *)((char *)bestFit + sizeof (memoryBlock));
    }
}

void t_free(void *ptr)
{
    if (ptr == NULL)
        return;

    memoryBlock *block = (memoryBlock *)((char *)ptr - sizeof(memoryBlock));

    if (block->free)
        return;

    block->free = 1;

    // Merge with the previous free block if any
    memoryBlock *prev = block->previous;
    memoryBlock *next = block->next;
    if (prev != NULL && prev->free)
    {
        prev->size += block->size + sizeof(memoryBlock);
        prev->next = next;
        if (next != NULL)
            next->previous = prev;
        block = prev;
    }

    // Merge with the next free block if any
    if (next != NULL && next->free)
    {
        block->size += next->size + sizeof(memoryBlock);
        block->next = next->next;
        if (next->next != NULL)
            next->next->previous = block;
    }

    // Remove the block from the linked list
    if (block == head)
        head = next;
    if (prev != NULL)
        prev->next = next;
    else
        head = next;
    if (next != NULL)
        next->previous = prev;
}

// implement a stack! relationship between stack and heap
void t_gcollect(void)
{
    memoryBlock *current = head;
    memoryBlock *prev = NULL;

    while (current != NULL)
    {
        if (current->free) {
            // If the block is free, try to merge it with adjacent free blocks
            memoryBlock *next = current->next;
            while (next != NULL && next->free) {
                current->size += next->size + sizeof(memoryBlock);
                current->next = next->next;
                if (next->next != NULL) {
                    next->next->previous = current;
                }
                next = next->next;
            }

            // Move to the next block
            prev = current;
            current = current->next;
        } else {
            // Check if the block is in use
            bool in_use = false;
            scanForPointers((char *)current + sizeof(memoryBlock),
                           (char *)current + current->size + sizeof(memoryBlock), &in_use);
            
            // If the block is not in use, free it
            if (!in_use) {
                if (prev == NULL) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                memoryBlock *next = current->next;
                munmap(current, current->size + sizeof(memoryBlock));
                current = next;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
}
