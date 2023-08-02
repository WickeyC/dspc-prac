// P3Q2.cpp : Defines the entry point for the console application.
//
//#include "stdio.h"
//#include "omp.h"
//
//static long num_steps = 100000;
//double step;
//
//int main()
//{
//    int i;
//    double x, pi, sum = 0.0;
//    step = 1.0 / (double)num_steps;
//
//    for (i = 0; i < num_steps; i++)
//    {
//        x = (i + 0.5) * step;
//        sum += 4.0 / (1.0 + x * x);
//    }
//    pi = step * sum;
//    printf("%f\n", pi);
//    return 0;
//}

// P3Q2.cpp : Defines the entry point for the console application.
//

#include "stdio.h"
#include "omp.h"
//set the thread numbers
#define NTHREAD 5

static long num_steps = 100000;
double step;

int main()
{
    int j;
    double x, pi = 0;
    //double sum = 0.0; //this will cause the sum to be different every time
    double sum[NTHREAD];
    step = 1.0 / (double)num_steps;

    //set the thread numebrs
    omp_set_num_threads(NTHREAD);

    //track the time
    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        int i;
        //NTHREAD
        int size = omp_get_num_threads();
        //id of the processor running
        int rank = omp_get_thread_num();
        for (i = 0, sum[rank] = 0.0; i < num_steps; i=i+size)
        {
            x = (i + 0.5) * step;
            sum[rank] += 4.0 / (1.0 + x * x);
        }
        printf("ID(%d) sum = %f\n", rank, sum[rank]);
    }
    double end_time = omp_get_wtime();

    for (j = 0; j < NTHREAD; j++) {
        pi += step * sum[j];
    }

    //pi = step * sum;
    printf("%f\n", pi);
    printf("Time used: %f", end_time - start_time);
    return 0;
}
