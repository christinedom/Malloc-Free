#include "libtdmm/tdmm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE 1
#define MAX_SIZE (8 * 1024 * 1024)

int main() {
    t_init(BEST_FIT, NULL);

    clock_t total_start = clock();
    double total_time = 0.0;

    for (size_t size = MIN_SIZE; size <= MAX_SIZE; size *= 2) {
        clock_t malloc_start = clock();
        void *ptr = t_malloc(size);
        clock_t malloc_end = clock();
        double malloc_time = ((double)(malloc_end - malloc_start)) / CLOCKS_PER_SEC;

        clock_t free_start = clock();
        t_free(ptr);
        clock_t free_end = clock();
        double free_time = ((double)(free_end - free_start)) / CLOCKS_PER_SEC;

        //printf("memory size (bytes) >> %zu\n", size);
        //printf("%f\n", malloc_time);
        printf(" %f\n", free_time);

        total_time += malloc_time + free_time;
    }

    clock_t total_end = clock();
    double overall_time = ((double)(total_end - total_start)) / CLOCKS_PER_SEC;

    printf("Overall time (seconds) >> %f\n", overall_time);
    printf("Overall speed (operations/second) >> %f\n", (double)(MIN_SIZE * 2 * (MAX_SIZE / MIN_SIZE)) / overall_time);

    return 0;
}