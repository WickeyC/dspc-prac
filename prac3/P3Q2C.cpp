#include "stdio.h"
#include "omp.h"
//set the thread numbers
#define NTHREAD 8

static long num_steps = 1000000;
double step;

int main()
{
    int i, j, size;
    double x, pi = 0.0;
    double sum = 0.0;
    step = 1.0 / (double)num_steps;

    for (j = 1; j <= NTHREAD; j++) {
        sum = 0.0;
        pi = 0.0;
        omp_set_num_threads(j);

        //track the time
        double start_time = omp_get_wtime();

        #pragma omp parallel 
        {
            #pragma omp single 
                size = omp_get_num_threads();
                printf("Number of threads: %d\n", size);
            

            #pragma omp for reduction(+ : sum)
            for (i = 0; i < num_steps; i++)
            {
                x = (i + 0.5) * step;
                sum += 4.0 / (1.0 + x * x);
            }

        }
        double end_time = omp_get_wtime();

        //sum will be total of all sum
        pi = step * sum;
        printf("%f\n", pi);
        printf("Time used: %f\n", (end_time - start_time));
    }
    return 0;
}
