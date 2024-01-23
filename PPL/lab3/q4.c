#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size, len1, len2, strlength1, strlength2, m;
    char str1[50], str2[50], str3[50], str4[50], res_str[100], str5[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0) {
        fprintf(stdout, "Enter string 1: ");
        fgets(str1, 50, stdin);
        fflush(stdout);
        fprintf(stdout, "Enter string 2: ");
        fgets(str2, 50, stdin);
        fflush(stdout);
        len1 = strcspn(str1, "\n");
        len2 = strcspn(str2, "\n");
        str1[len1]='\0';
        str2[len2]='\0';
        strlength1=strlen(str1);
        strlength2=strlen(str2);
        if(strlength1!=strlength2) {
            fprintf(stdout, "Lengths not equal");
            fflush(stdout);
            return 1;
        }
        m=strlength1/size; //no. of characters passed to each single process
    }
    MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(str1,m,MPI_CHAR,&str3,m,MPI_CHAR,0,MPI_COMM_WORLD);
    MPI_Scatter(str2,m,MPI_CHAR,&str4,m,MPI_CHAR,0,MPI_COMM_WORLD);
    for (int i=0; i<2*m; i=i+2) {
        res_str[i]=str3[i/2];
        res_str[i+1]=str4[i/2];
    }
    MPI_Gather(&res_str,2*m,MPI_CHAR,str5,2*m,MPI_CHAR,0,MPI_COMM_WORLD);
    if(rank==0) {
        res_str[2*m]='\0';
        fprintf(stdout, "Resultant string: %s", str5);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}