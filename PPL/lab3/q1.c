#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, A[20], c, B[20], sum = 0, fact = 1;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        fprintf(stdout, "Enter %d elements: ", size);
        fflush(stdout);
        for (int i = 0; i < size; i++)
        {
            scanf("%d", &A[i]);
        }
    }
    MPI_Scatter(A, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD);
    fprintf(stdout, "Rank: %d   Received: %d\n", rank, c);
    fflush(stdout);
    for (int i = 1; i <= c; i++)
    {
        fact = fact * i;
    }
    c = fact;
    MPI_Gather(&c, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);
    fprintf(stdout, "Received from rank: %d  Factorial: %d\n", rank, c);
    fflush(stdout);
    if (rank == 0)
    {
        for (int i = 0; i < size; i++)
        {
            sum += B[i];
        }
        fprintf(stdout, "Sum: %d\n", sum);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}