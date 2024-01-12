#include <mpi.h>
#include <stdio.h>

int is_prime(int n) {
    if(n<=1)
        return 0;
    for(int i=2; i*i<=n; i++) {
        if(n%i==0)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size!=2) {
        printf("This program is for 2 processes.\n");
        MPI_Finalize();
        return 1;
    }

    if(rank==0) {
        for(int i=1; i<=50; i++) {
            if(is_prime(i))
                printf("Rank %d found prime number %d\n", rank, i);
        }
    }
    else {
        for(int i=51; i<=100; i++) {
            if(is_prime(i))
                printf("Rank %d found prime number %d\n", rank, i);
        }
    }
    MPI_Finalize();
    return 0;
}