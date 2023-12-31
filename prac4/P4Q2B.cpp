// P4Q2.cpp : Defines the entry point for the console application.
//

// OUTPUT:
// 4999999.500000
// Original work took 0.020831 seconds

#include <stdio.h>
#include <cstdlib>
#include "omp.h"
#define NTHREAD 5

const long MAX = 10000000;

int main()
{
    double total = 0.0, * A;
    int i;

    A = (double*)malloc(MAX * sizeof(double));
    if (A == NULL) {
        printf("Insufficient memory! Can't continue. Terminating the program abruptly.\n");
        return -1;
    }

    for (i = 0; i < MAX; i++)
    {
        A[i] = (double)i;
    }

    //set the thread numebrs
    omp_set_num_threads(NTHREAD);

    double start_time = omp_get_wtime();

    #pragma parallel omp for reduction (+:total)
    for (i = 0, total = 0.0; i < MAX; i++) {
        total += A[i];
    }

    double end_time = omp_get_wtime();
    total = total / MAX;
    printf("%f\n", total);
    printf("Original work took %f seconds\n", end_time - start_time);
    free(A);
    return 0;
}