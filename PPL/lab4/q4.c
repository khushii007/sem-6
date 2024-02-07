#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    int rank, size, mat[4][4], mat2[4], mat4[4], mat3[4][4];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0) {
        printf("Enter 4X4 elements: ");
        for(int i=0; i<4; i++) {
            for(int j=0; j<4; j++) {
                scanf("%d", &mat[i][j]);
            }
        }
    }
    MPI_Scatter(mat,4,MPI_INT,mat2,4,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scan(&mat2,&mat4,4,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    MPI_Gather(mat4,4,MPI_INT,mat3,4,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0) {
        printf("Output: \n");
        for(int i=0; i<4; i++) {
            for(int j=0; j<4; j++) {
                printf("%d ", mat3[i][j]);
            }
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}