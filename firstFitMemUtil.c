#include "libtdmm/tdmm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE 1
#define MAX_SIZE (8 * 1024 * 1024)

int main() {
    t_init(FIRST_FIT, NULL);
    size_t total_memory = 0;
    size_t used_memory = 0;
    clock_t start = clock();
    clock_t prev = start;

    for (size_t size = MIN_SIZE; size <= MAX_SIZE; size *= 2) {
        clock_t malloc_start = clock();
        void *ptr = t_malloc(size);
        if (ptr) {
            used_memory += size;
            total_memory += size;
        }
        clock_t malloc_end = clock();
        double malloc_time = ((double)(malloc_end - malloc_start)) / CLOCKS_PER_SEC;
        clock_t end = clock();
        double current_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        double time_elapsed = current_time - ((double)(prev - start)) / CLOCKS_PER_SEC;
        prev = end;

        double memory_utilization = (double)used_memory / total_memory * 100;
        printf("Time: %.9f seconds, Memory Utilization: %.2f%%\n", current_time, memory_utilization);

        clock_t malloc_start2 = clock();
        ptr = t_malloc(size);
        if (ptr) {
            used_memory += size;
            total_memory += size;
        }
        clock_t malloc_end2 = clock();
        double malloc_time2 = ((double)(malloc_end2 - malloc_start2)) / CLOCKS_PER_SEC;
        end = clock();
        current_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        time_elapsed = current_time - ((double)(prev - start)) / CLOCKS_PER_SEC;
        prev = end;

        memory_utilization = (double)used_memory / total_memory * 100;
        printf("Time: %.9f seconds, Memory Utilization: %.2f%%\n", current_time, memory_utilization);

        clock_t free_start = clock();
        t_free(ptr);
        used_memory -= size;
        clock_t free_end = clock();
        double free_time = ((double)(free_end - free_start)) / CLOCKS_PER_SEC;
        end = clock();
        current_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        time_elapsed = current_time - ((double)(prev - start)) / CLOCKS_PER_SEC;
        prev = end;

        memory_utilization = (double)used_memory / total_memory * 100;
        printf("Time: %.9f seconds, Memory Utilization: %.2f%%\n", current_time, memory_utilization);
    }

    return 0;
}