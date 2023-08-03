//MODIFIED:

// P4Q1.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "omp.h"
#define NUM_THREADS 6
static long num_steps = 100000;
double step;

int main()
{
    int i, nthreads;
    double pi = 0;
    step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    double start_time = omp_get_wtime();
#pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        double sum;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) {
            nthreads = nthrds;
            printf("Total OMP threads: %d\n", nthreads);
        }

        for (i = id, sum = 0.0; i < num_steps; i = i + nthrds)
        {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        // CRITICAL REGION
        // only one thread entry to prevent same cache line
        #pragma omp critical
        pi += sum * step;
    }
    //for (i = 0, pi = 0.0; i < nthreads; i++) {
    //    sum += partial_sums[i];
    //}
    //pi = sum * step;
    double end_time = omp_get_wtime();

    printf("%f\n", pi);

    printf("Work took %f seconds\n", end_time - start_time);
    return 0;
}

//ORIGINAL:

// P4Q1.cpp : Defines the entry point for the console application.
//

//#include <stdio.h>
//#include "omp.h"
//#define NUM_THREADS 4
//static long num_steps = 100000;
//double step;
//
//int main()
//{
//    int i, nthreads;
//    double pi = 0;
//    double partial_sums[NUM_THREADS], sum = 0.0;
//    step = 1.0 / (double)num_steps;
//    omp_set_num_threads(NUM_THREADS);
//    double start_time = omp_get_wtime();
//#pragma omp parallel
//    {
//        int i, id, nthrds;
//        double x;
//        id = omp_get_thread_num();
//        nthrds = omp_get_num_threads();
//        if (id == 0) {
//            nthreads = nthrds;
//            printf("Total OMP threads: %d\n", nthreads);
//        }
//
//        for (i = id, partial_sums[id] = 0.0; i < num_steps; i = i + nthrds)
//        {
//            x = (i + 0.5) * step;
//            partial_sums[id] += 4.0 / (1.0 + x * x);
//        }
//    }
//    for (i = 0, pi = 0.0; i < nthreads; i++) {
//        sum += partial_sums[i];
//    }
//    pi = sum * step;
//    double end_time = omp_get_wtime();
//
//    printf("%f\n", pi);
//
//    printf("Work took %f seconds\n", end_time - start_time);
//    return 0;
//}
