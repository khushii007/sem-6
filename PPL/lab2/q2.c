#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, n;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0) {
        printf("Enter a number: ");
        scanf("%d", &n);
        for(int i=1; i<size; i++) {
            MPI_Send(&n,1,MPI_INT,i,1,MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Recv(&n,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        fprintf(stdout, "Rank: %d   Received: %d\n", rank, n);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}