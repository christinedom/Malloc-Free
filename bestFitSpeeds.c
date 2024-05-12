#include "libtdmm/tdmm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE 1
#define MAX_SIZE (8 * 1024 * 1024)

int main() {
    clock_t start, end;
    double total_time = 0.0;

    start = clock();
    t_init(BEST_FIT, NULL);
    for (size_t size = MIN_SIZE; size <= MAX_SIZE; size *= 2) {
        double malloc_time = 0.0;
        double free_time = 0.0;

        void *ptr = t_malloc(size);
        malloc_time = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        t_free(ptr);
        free_time = ((double)(clock() - start)) / CLOCKS_PER_SEC;

    
    }
    end = clock();
    total_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Total program execution time: %f seconds\n", total_time);

    return 0;
}