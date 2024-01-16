#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, n, value;
    int buffer[100];
    int bufSize = 100;
    MPI_Status status;
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    
    if(rank==0) {
        int array[size-1];
        printf("Enter elements: ");
        for(int i=0; i<size-1; i++) {
            scanf("%d",&array[i]);
        }
        for(int i=1; i<size; i++) {
            MPI_Buffer_attach(buffer, bufSize);
            MPI_Bsend(&array[i-1],1,MPI_INT,i,1,MPI_COMM_WORLD);
            MPI_Buffer_detach(&buffer, &bufSize);
        }
    }
    else {
        MPI_Recv(&value,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        if(rank%2==0) {
            n = value*value;
        }
        else {
            n = value*value*value;
        }
        fprintf(stdout,"Rank: %d  Number:%d  Output number: %d\n", rank, value, n);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}