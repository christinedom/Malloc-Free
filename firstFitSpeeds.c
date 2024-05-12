#include "libtdmm/tdmm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE 1
#define MAX_SIZE (8 * 1024 * 1024)

int main() {
    t_init(FIRST_FIT, NULL);

    for (size_t size = MIN_SIZE; size <= MAX_SIZE; size *= 2) {
        clock_t start, end;
        double malloc_time = 0.0;
        double free_time = 0.0;

        start = clock();
        void *ptr = t_malloc(size);
        end = clock();
        malloc_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        t_free(ptr);
        end = clock();
        free_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    return 0;
}