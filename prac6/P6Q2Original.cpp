// This program is to caculate PI using MPI
// The algorithm is based on integral representation of PI. If f(x)=4/(1+x^2), then PI is the intergral of f(x) from 0 to 1

#include <stdio.h>
#include <mpi.h>

#define N 1E7
#define d 1E-7
#define d2 1E-14

int main(int argc, char* argv[])
{
    int rank, size, error, i;
    double pi = 0.0, result = 0.0, sum = 0.0, begin = 0.0, end = 0.0, x2;
    MPI_Init(&argc, &argv);

    //Get process ID


    //Get total processes Number


    //Synchronize all processes and get the begin time


    begin = MPI_Wtime();

    //Each process will caculate a part of the sum
    for (i = rank; i < N; i += size)
    {
        x2 = d2 * i * i;
        result += 1.0 / (1.0 + x2);
    }

    //Sum up all results


    //Synchronize all processes and get the end time


    end = MPI_Wtime();

    //Caculate and print PI
    if (rank == 0)
    {
        pi = 4 * d * sum;
        printf("np=%2d;    Time=%fs;    PI=%lf\n", size, end - begin, pi);
    }

    //Finalizing


    return 0;
}