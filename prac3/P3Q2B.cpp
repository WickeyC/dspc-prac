#include "stdio.h"
#include "omp.h"
//set the thread numbers
#define NTHREAD 8
#define PAD 1

static long num_steps = 1000000;
double step;

int main()
{
    int j;
    double x, pi = 0;
    //double sum = 0.0; //this will cause the sum to be different every time
    double sum[NTHREAD][PAD];
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
        for (i = 0, sum[rank][0] = 0.0; i < num_steps; i = i + size)
        {
            x = (i + 0.5) * step;
            sum[rank][0] += 4.0 / (1.0 + x * x);
        }
        printf("ID(%d) sum = %f\n", rank, sum[rank][0]);
    }
    double end_time = omp_get_wtime();

    for (j = 0; j < NTHREAD; j++) {
        pi += step * sum[j][0];
    }

    //pi = step * sum;
    printf("%f\n", pi);
    printf("Time used: %f", end_time - start_time);
    return 0;
}
