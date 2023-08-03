// P4Q2.cpp : Defines the entry point for the console application.
//

// Output:
// 49999.500000
// Original work took 0.020659 seconds

#include <stdio.h>
#include <cstdlib>
#include "omp.h"

const long MAX = 10000000;

int main()
{
    double ave = 0.0, * A;
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
    double start_time = omp_get_wtime();

    for (i = 0; i < MAX; i++) {
        ave += A[i];
    }
    double end_time = omp_get_wtime();
    ave = ave / MAX;
    printf("%f\n", ave);
    printf("Original work took %f seconds\n", end_time - start_time);
    free(A);
    return 0;
}