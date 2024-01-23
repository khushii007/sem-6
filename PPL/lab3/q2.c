#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, m, A[100], B[100], sum = 0, avg_sum = 0;
    double avg, avg_avg, C[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n = size;

    if (rank == 0)
    {
        fprintf(stdout, "Enter an integer: ");
        scanf("%d", &m);
        fflush(stdout);
        fprintf(stdout, "Enter %d elements: ", n * m);
        for (int i = 0; i < n * m; i++)
        {
            scanf("%d", &A[i]);
        }
        fflush(stdout);
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD); // broadcast
    MPI_Scatter(A, m, MPI_INT, B, m, MPI_INT, 0, MPI_COMM_WORLD);
    fprintf(stdout, "\nRank: %d   Received: ", rank);
    for (int i = 0; i < m; i++)
    {
        fprintf(stdout, "%d, ", B[i]);
    }
    fflush(stdout);
    for (int i = 0; i < m; i++)
    {
        sum += B[i];
    }
    avg = (double)sum / m;
    fprintf(stdout, "   Avg: %lf", avg);
    fflush(stdout);
    MPI_Gather(&avg, 1, MPI_DOUBLE, C, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            avg_sum += C[i];
        }
        avg_avg = (double)avg_sum / n;
        fprintf(stdout, "\nAverage of averages: %lf", avg_avg);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}