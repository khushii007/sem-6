#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size, strlength, len, m, non_vowel = 0, count[25], totalCount = 0;
    char str[50], str2[25];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        fprintf(stdout, "Enter a string (evenly divisible among all the processes): ");
        fgets(str, 50, stdin);
        fflush(stdout);
        len = strcspn(str, "\n");
        str[len] = '\0';
        strlength = strlen(str);
        // fprintf(stdout, "%d", strlength);
        m = strlength / size;
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(str, m, MPI_CHAR, &str2, m, MPI_CHAR, 0, MPI_COMM_WORLD);
    fprintf(stdout, "\nRank: %d  Received: ", rank);
    for (int i = 0; i < m; i++)
    {
        fprintf(stdout, "%c", str2[i]);
    }
    fflush(stdout);
    for (int i = 0; i < m; i++)
    {
        if (str2[i] != 'a' && str2[i] != 'e' && str2[i] != 'i' && str2[i] != 'o' && str2[i] != 'u' && str2[i] != 'A' && str2[i] != 'E' && str2[i] != 'I' && str2[i] != 'O' && str2[i] != 'U')
        {
            non_vowel += 1;
        }
    }
    /*fprintf(stdout, "  Non vowels: %d", non_vowel);
    fflush(stdout);*/
    MPI_Gather(&non_vowel, 1, MPI_INT, count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        fprintf(stdout,"\nVowels received from processes: ");
        fflush(stdout);
        for (int i=0; i<size; i++) {
            fprintf(stdout, "%d, ", count[i]);
            fflush(stdout);
        }
        for (int i = 0; i < m; i++)
        {
            totalCount += count[i];
        }
        fprintf(stdout, "\nTotal non vowels: %d", totalCount);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}