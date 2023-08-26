// P6Q4.cpp : Defines the entry point for the console application.
//

#include "stdio.h"
#include "mpi.h"

int main(int argc, char** argv)
{
    int rank, value, size;
    MPI_Status status;




    do {
        if (rank == 0) {
            scanf_s("%d", &value);


        }
        else {


            if (rank < size - 1)


        }
        printf("Process %d got %d\n", rank, value);



    } while (value >= 0);

    MPI_Finalize();
    return 0;
}