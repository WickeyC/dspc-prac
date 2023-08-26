// mpiexec -np 4 P6Q3

#include "stdio.h"
#include "mpi.h"

int main(int argc, char** argv)
{
    int rank = 0, size = 0, value = 0;
    double begin = 0.0, end = 0.0;

    MPI_Init(&argc, &argv);

    //Get process ID
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //Get total processes Number
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    begin = MPI_Wtime();

    do {
        if (rank == 0)
            scanf_s("%d", &value);
        //Broadcast the input value to all the processes
        MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);

        printf("Process %d got %d\n", rank, value);

        fflush(stdout);
    } while (value >= 0);;

    end = MPI_Wtime();

    //Finalizing
    MPI_Finalize();

    return 0;
}