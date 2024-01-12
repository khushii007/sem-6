#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char str[6] = "Hello"; //space for null terminator
    int len = strlen(str);

    if(rank >= len) {
        printf("Rank greater than string length\n");
    }
    else {
        if(str[rank]>=65 && str[rank]<=90) {
            str[rank] += 32;
            printf("Rank: %d   String: %s\n", rank, str);
        }
        else if(str[rank]>=97 && str[rank]<=122) {
            str[rank] -= 32;
            printf("Rank: %d   String: %s\n", rank, str);
        }
        else {
            printf("Rank: %d   String: %s\n", rank, str);
        }
    }    
    MPI_Finalize();
    return 0;
}