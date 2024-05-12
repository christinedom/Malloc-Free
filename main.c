#include "libtdmm/tdmm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_ALLOCATIONS 1000000
#define MAX_ALLOCATION_SIZE (1024 * 1024) // 1MB
#define MEMORY (64 * 64 * 1024) // 64 MB

typedef struct block {
    size_t size;
    int free;
    struct block *next;
    struct block *previous;
} memoryBlock;

// double calculate_memory_utilization() {
//     size_t total_allocated = 0;
//     size_t total_requested = 0;

//     for (size_t i = 0; i < MAX_ALLOCATIONS; i++) {
//         size_t request_size = rand() % MAX_ALLOCATION_SIZE + 1;
//         void *ptr = t_malloc(request_size);
//         if (ptr != NULL) {
//             total_allocated += ALIGN(request_size + sizeof(memoryBlock), sysconf(_SC_PAGESIZE));
//             total_requested += request_size;
//             t_free(ptr);
//         }
//     }

//     return (double)total_requested / total_allocated * 100;
// }

int main(int argc, char *argv[]) {
    // clock_t start, end;
    // double time_taken = 0;

    // t_init(BEST_FIT, NULL);
    // printf("Test Case 1: Initialize a memory allocator with NULL stack bottom pointer\n");
    // start = clock();
    // t_init(BEST_FIT, NULL);
    // end = clock();
    // time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Time: %f seconds\n", time_taken);

    // double total_memory_utilization = 0.0;
    // size_t num_measurements = 0;

    // start = clock();
    // for (size_t i = 0; i < MAX_ALLOCATIONS; i++) {
    //     size_t request_size = rand() % MAX_ALLOCATION_SIZE + 1;
    //     void *ptr = t_malloc(request_size);
    //     if (ptr != NULL) {
    //         t_free(ptr);
    //     }

    //     // Calculate memory utilization every 1000 iterations
    //     if (i % 1000 == 0) {
    //         double current_utilization = calculate_memory_utilization();
    //         total_memory_utilization += current_utilization;
    //         num_measurements++;
    //     }
    // }
    // end = clock();
    // time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Time for malloc/free: %f seconds\n", time_taken);

    // double avg_memory_utilization = total_memory_utilization / num_measurements;
    // printf("Average Memory Utilization: %.2f%%\n", avg_memory_utilization);

    // return 0;
}