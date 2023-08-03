// P4Q2.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <cstdlib>
#include "omp.h"
#define NTHREAD 5

const long MAX = 100000;

int main()
{
    double total = 0.0, average, * A;
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

    #pragma omp parallel 
    {
        int i;
        double localTotal;
        //NTHREAD
        int size = omp_get_num_threads();
        //id of the processor running
        int rank = omp_get_thread_num();

        for (i = rank, localTotal = 0.0; i < MAX; i = i + size) {
            localTotal += A[i];
        }

        #pragma omp critical 
        total += localTotal;
    }

    double end_time = omp_get_wtime();
    average = total / MAX;
    printf("%f\n", average);
    printf("Original work took %f seconds\n", end_time - start_time);
    free(A);
    return 0;
}

