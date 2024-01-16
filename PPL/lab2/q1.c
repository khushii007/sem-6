#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char str[20], toggled_str[20];
    int rank, size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if(rank==0) {
        printf("Enter a word: ");
        fgets(str, sizeof(str), stdin);
        MPI_Ssend(&str,sizeof(str),MPI_CHAR,1,1,MPI_COMM_WORLD);
        MPI_Recv(&toggled_str,sizeof(toggled_str),MPI_CHAR,1,1,MPI_COMM_WORLD,&status);
        fprintf(stdout,"Toggled word: %s", toggled_str);
        fflush(stdout);
    }
    else if(rank==1) {
        MPI_Recv(&str,sizeof(str),MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
        int len = strlen(str);
        for(int i=0; i<len; i++) {
            if(str[i]>=65 && str[i]<=90) {
                toggled_str[i] = str[i] + 32;
            }
            else if(str[i]>=97 && str[i]<=122) {
                toggled_str[i] = str[i] - 32;
            }
            else {
                toggled_str[i]=str[i];
            }
        }
        MPI_Ssend(&toggled_str,sizeof(toggled_str),MPI_CHAR,0,1,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}