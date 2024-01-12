#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int a=10, b=2;
    if(rank == 0) {
        printf("a+b = %d\n", a+b);
    }
    else if(rank ==1) {
        printf("a-b = %d\n", a-b);
    }
    else if(rank==2) {
        printf("a*b = %d\n", a*b);
    }
    else if(rank==3){
        printf("a/b = %d\n", a/b);
    }
    else {
        printf("Rank is greater than 3\n");
    }
    MPI_Finalize();
    return 0;
}