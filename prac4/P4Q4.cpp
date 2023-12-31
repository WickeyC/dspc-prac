// MODIFIED:

// P4Q4.cpp : Defines the entry point for the console application.
//

// atomic is similar to lock. (critical)

// OUTPUT (Consistent):
// The sum is 4999947776.000000 and 9999780864.000000
// The sum is 4999947776.000000 and 9999780864.000000
// The sum is 4999947776.000000 and 9999780864.000000
// The sum is 4999947776.000000 and 9999780864.000000
// The sum is 4999947776.000000 and 9999780864.000000

#include <stdio.h>
#include "omp.h"

float work1(int i) {
    return 1.0 * i;
}

float work2(int i) {
    return 2.0 * i;
}
float Sum_array(int nval, float* A) {
    float sum = 0.0;
    for (int i = 0; i < nval; i++) sum = sum + A[i];
    return sum;
}

void atomic_example(float* x, float* y, int* index, int n) {
    int i;

#pragma omp parallel for shared(x, y, index, n)
    for (i = 0; i < n; i++) {
        #pragma omp atomic
        x[index[i]] += work1(i);
        #pragma omp atomic
        y[i] += work2(i);
    }
}

int main() {
    float x[10000];
    float y[100000];
    int index[100000];
    float sum1, sum2;
    int i;

    for (i = 0; i < 100000; i++) {
        index[i] = i % 1000;
        y[i] = 0.0;
    }
    for (i = 0; i < 10000; i++)
        x[i] = 0.0;
    atomic_example(x, y, index, 100000);

    sum1 = Sum_array(10000, x);
    sum2 = Sum_array(100000, y);

    printf(" The sum is %f and %f\n", sum1, sum2);
    return 0;
}