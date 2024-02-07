#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank, size, fact = 1, factSum, error, error_class;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    for (int i = 1; i <= rank; i++)
    {
        fact = fact * i;
    }
    error = MPI_Scan(&fact, &factSum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    if (error != MPI_SUCCESS)
    {
        char error_string[100];
        int len;
        MPI_Error_class(error, &error_class);              // retrives error class associated with the error code 'error'
        MPI_Error_string(error_class, error_string, &len); // converts error class to human readable format
        printf("\nError class: %s", error_string);
        MPI_Error_string(error, error_string, &len);
        printf("\nError string: %s", error_string);
        //MPI_Abort(MPI_COMM_WORLD, error);
        return 1;
    }
    printf("\nRank: %d      Current sum: %d", rank, factSum);
    MPI_Finalize();
    return 0;
}