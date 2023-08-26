// mpiexec -np 4 P6Q3

#include "stdio.h"
#include "mpi.h"

int main(int argc, char** argv)
{
    int rank = 0, value = 0;



    do {
        if (rank == 0)
            scanf_s("%d", &value);
        //Broadcast the input value to all the processes


        printf("Process %d got %d\n", rank, value);


    } while (value >= 0);


    return 0;
}