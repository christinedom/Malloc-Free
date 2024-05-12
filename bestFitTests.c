#include "libtdmm/tdmm.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void run_test_case(int test_case) {
    clock_t start, end;
    double time_taken = 0;

    t_init(BEST_FIT, NULL);

    if (test_case == 1) {

        start = clock();
        t_init(FIRST_FIT, NULL);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 2) {

        start = clock();
        void *stack_bottom = malloc(1024);
        t_init(FIRST_FIT, stack_bottom);
        free(stack_bottom);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 3) {

        start = clock();
        void *ptr1 = t_malloc(100);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 4) {

        start = clock();
        void *ptr2 = t_malloc(200);
        t_free(ptr2);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 5) {

        start = clock();
        for (int i = 0; i < 15; i++) {
            void *ptr = t_malloc(50 * (i + 1));
        }
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 6) {

        start = clock();
        void *ptrs[15];
        for (int i = 0; i < 15; i++) {
            ptrs[i] = t_malloc(50 * (i + 1));
        }
        for (int i = 0; i < 15; i++) {
            t_free(ptrs[i]);
        }
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 7) {

        start = clock();
        void *ptr3 = t_malloc(5000);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 8) {

        start = clock();
        void *invalid_ptr = NULL;
        t_free(invalid_ptr);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 9) {

        start = clock();
        void *ptr4 = t_malloc(100);
        for (int i = 0; i < 3; i++) {
            t_free(ptr4);
        }
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 10) {

        start = clock();
        void *large_ptr = t_malloc(1000000);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 11) {

        start = clock();
        void *large_ptr2 = t_malloc(1000000);
        memset(large_ptr2, 0, 1000000);
        t_free(large_ptr2);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 12) {

        start = clock();
        void *ptr_mfmf1, *ptr_mfmf2;
        ptr_mfmf1 = t_malloc(100);
        t_free(ptr_mfmf1);
        ptr_mfmf2 = t_malloc(200);
        t_free(ptr_mfmf2);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 13) {

        start = clock();
        void *ptr_mmff1, *ptr_mmff2;
        ptr_mmff1 = t_malloc(100);
        ptr_mmff2 = t_malloc(200);
        t_free(ptr_mmff1);
        t_free(ptr_mmff2);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 14) {

        start = clock();
        void *ptr_mmff3, *ptr_mmff4;
        ptr_mmff3 = t_malloc(100);
        ptr_mmff4 = t_malloc(200);
        t_free(ptr_mmff4);
        t_free(ptr_mmff3);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 15) {

        start = clock();
        void *ptr_mmfmff1, *ptr_mmfmff2, *ptr_mmfmff3;
        ptr_mmfmff1 = t_malloc(100);
        ptr_mmfmff2 = t_malloc(200);
        t_free(ptr_mmfmff1);
        ptr_mmfmff3 = t_malloc(300);
        t_free(ptr_mmfmff2);
        t_free(ptr_mmfmff3);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 16) {

        start = clock();
        void *ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[30];
        for (int i = 0; i < 5; i++) {
            ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[i] = t_malloc(100 * (i + 1));
        }
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[0]);
        for (int i = 5; i < 10; i++) {
            ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[i] = t_malloc(100 * (i + 1));
        }
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[6]);
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[5]);
        for (int i = 10; i < 13; i++) {
            ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[i] = t_malloc(100 * (i + 1));
        }
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[12]);
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[11]);
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[10]);
        for (int i = 13; i < 15; i++) {
            ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[i] = t_malloc(100 * (i + 1));
        }
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[14]);
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[13]);
        for (int i = 15; i < 18; i++) {
            ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[i] = t_malloc(100 * (i + 1));
        }
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[17]);
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[16]);
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[15]);
        for (int i = 18; i < 22; i++) {
            ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[i] = t_malloc(100 * (i + 1));
        }
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[21]);
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[20]);
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[19]);
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[18]);
        for (int i = 22; i < 24; i++) {
            ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[i] = t_malloc(100 * (i + 1));
        }
        t_free(ptrs_mmmmmfmmmmffmmmfffmmffffmfffff[22]);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 17) {

        start = clock();
        void *ptrs_mfmfmfmfmfmfmf[14];
        for (int i = 0; i < 14; i++) {
            ptrs_mfmfmfmfmfmfmf[i] = t_malloc(100 * (i + 1));
            t_free(ptrs_mfmfmfmfmfmfmf[i]);
        }
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 18) {

        start = clock();
        void *ptrs_mmffmmffmmffmmffmmffmmffmmff[14];
        for (int i = 0; i < 14; i += 2) {
            ptrs_mmffmmffmmffmmffmmffmmffmmff[i] = t_malloc(100 * (i + 1));
            ptrs_mmffmmffmmffmmffmmffmmffmmff[i + 1] = t_malloc(100 * (i + 2));
            t_free(ptrs_mmffmmffmmffmmffmmffmmffmmff[i]);
            t_free(ptrs_mmffmmffmmffmmffmmffmmffmmff[i + 1]);
        }
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 19) {

        start = clock();
        void *ptr_mfmmffmmmfff1, *ptr_mfmmffmmmfff2, *ptr_mfmmffmmmfff3, *ptr_mfmmffmmmfff4, *ptr_mfmmffmmmfff5;
        ptr_mfmmffmmmfff1 = t_malloc(1000000);
        t_free(ptr_mfmmffmmmfff1);
        ptr_mfmmffmmmfff2 = t_malloc(2000000);
        ptr_mfmmffmmmfff3 = t_malloc(3000000);
        t_free(ptr_mfmmffmmmfff2);
        t_free(ptr_mfmmffmmmfff3);
        ptr_mfmmffmmmfff4 = t_malloc(4000000);
        ptr_mfmmffmmmfff5 = t_malloc(5000000);
        ptr_mfmmffmmmfff4 = t_malloc(4000000);
        t_free(ptr_mfmmffmmmfff4);
        t_free(ptr_mfmmffmmmfff5);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_taken);
    } else if (test_case == 20) {

        start = clock();
        void *ptr_mmfmmmff1, *ptr_mmfmmmff2, *ptr_mmfmmmff3, *ptr_mmfmmmff4;
        ptr_mmfmmmff1 = t_malloc(1000000);
        ptr_mmfmmmff2 = t_malloc(2000000);
        t_free(ptr_mmfmmmff2);
    }
}

int main () {

  printf("best fit test cases\n");

  for (int i = 1; i <= 20; i++) {
    run_test_case (i);
    printf("\n");
  }

  return 0;
}
