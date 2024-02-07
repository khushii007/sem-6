#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank, size, mat[3][3], rcvMat[3], ele, count = 0, total;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int error_code;
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN); // Set error handler to MPI_ERRORS_RETURN

    if (rank == 0)
    {
        printf("Enter matrix elements: ");
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                scanf("%d", &mat[i][j]);
            }
        }
        printf("Enter element to search: ");
        scanf("%d", &ele);
    }
    error_code = MPI_Bcast(&ele, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (error_code != MPI_SUCCESS) {
        char error_string[MPI_MAX_ERROR_STRING];
        int length;
        MPI_Error_string(error_code, error_string, &length);
        printf("Error in MPI_Bcast: %s\n", error_string);
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }

    error_code = MPI_Scatter(mat, 3, MPI_INT, rcvMat, 3, MPI_INT, 0, MPI_COMM_WORLD);
    if (error_code != MPI_SUCCESS) {
        char error_string[MPI_MAX_ERROR_STRING];
        int length;
        MPI_Error_string(error_code, error_string, &length);
        printf("Error in MPI_Scatter: %s\n", error_string);
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }

    printf("\nRank: %d    Received: ", rank);
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", rcvMat[i]);
        if (rcvMat[i] == ele)
            count++;
    }

    printf("    Element count: %d", count);
    error_code = MPI_Reduce(&count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (error_code != MPI_SUCCESS) {
        char error_string[MPI_MAX_ERROR_STRING];
        int length;
        MPI_Error_string(error_code, error_string, &length);
        printf("Error in MPI_Reduce: %s\n", error_string);
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }

    if (rank == 0)
    {
        printf("\nTotal occurrences: %d\n", total);
    }
    MPI_Finalize();
    return 0;
}
