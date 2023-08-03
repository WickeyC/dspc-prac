//MODIFIED:

// P4Q3.cpp : Defines the entry point for the console application.
//

// OUTPUT:
// Thread Producer 0: Start
// Thread Consumer 1: Done!
// In 0.003975 seconds, The sum is 1633995835.000000

// one section is done by one thread.

#include <stdio.h>
#include <cstdlib>
#include "omp.h"
#define NTHREAD 2

const int N = 100000;

void fill_rand(int nval, double* A) {
    for (int i = 0; i < nval; i++) A[i] = (double)rand();
}

double Sum_array(int nval, double* A) {
    double sum = 0.0;
    for (int i = 0; i < nval; i++)
        sum = sum + A[i];
    return sum;
}

int main() {
    double* A, sum, runtime;	
    int flag = 0;

    A = (double*)malloc(N * sizeof(double));
    srand(100);

    runtime = omp_get_wtime();

    #pragma omp parallel sections num_threads(NTHREAD) 
    {
        #pragma omp section
        {
            printf_s("Thread Producer %d: Start\n", omp_get_thread_num());
            fill_rand(N, A);	// Producer: fill an array of data 
            flag = 1;
            #pragma omp flush(flag)
        }
        #pragma omp section
        {
            while (!flag) {
                #pragma omp flush (flag)
            }
            sum = Sum_array(N, A);	// Consumer: sum the array  
            printf_s("Thread Consumer %d: Done!\n", omp_get_thread_num());
    
        }
    }
    
    runtime = omp_get_wtime() - runtime;

    printf(" In %lf seconds, The sum is %lf \n", runtime, sum);

    return 0;
}

//ORIGINAL:

// P4Q3.cpp : Defines the entry point for the console application.
//

//#include <stdio.h>
//#include <cstdlib>
//#include "omp.h"
//
//const int N = 100000;
//
//void fill_rand(int nval, double* A) {
//    for (int i = 0; i < nval; i++) A[i] = (double)rand();
//}
//
//double Sum_array(int nval, double* A) {
//    double sum = 0.0;
//    for (int i = 0; i < nval; i++)
//        sum = sum + A[i];
//    return sum;
//}
//
//int main() {
//    double* A, sum, runtime;	
//    int flag = 0;
//
//    A = (double*)malloc(N * sizeof(double));
//    srand(100);
//
//    runtime = omp_get_wtime();
//    fill_rand(N, A);	// Producer: fill an array of data 
//    sum = Sum_array(N, A);	// Consumer: sum the array 
//    runtime = omp_get_wtime() - runtime;
//
//    printf(" In %lf seconds, The sum is %lf \n", runtime, sum);
//
//    return 0;
//}