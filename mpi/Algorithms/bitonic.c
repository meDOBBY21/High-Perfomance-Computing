#include <stdio.h>
#include <mpi.h>
#include <math.h>
void compare_exchange_min(int *num, int *buff)
{
    if (*num > *buff)
        *num = *buff;
    return;
}

void compare_exchange_max(int *num, int *buff)
{
    if (*num < *buff)
        *num = *buff;
    return;
}

void bitonicSort(int rank, int *num, int p)
{
    MPI_Status status;
    int i, j, partner, buff, mask = 0, d,i_maker,j_maker;
    d = log2(p);
    for (i = 0; i < d; i++)
    {
        for (j = i; j >= 0; j--)
        {
            i_maker=(int)(pow(2,i));
            j_maker=(int)(pow(2,j));
            partner = rank^(j_maker);
            i_maker=(i_maker*2)&rank;
            j_maker=j_maker&rank;
            if ((j_maker==0 && i_maker==0)||(j_maker!=0 && i_maker!=0))
            {
                MPI_Send(num, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
                MPI_Recv(&buff, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
                compare_exchange_min(num, &buff);
            }
            else
            {
                MPI_Send(num, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
                MPI_Recv(&buff, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
                compare_exchange_max(num, &buff);
            }
        }
    }
}

int main(int argc, char **argv)
{
    int rank = 0, size = 0, i = 0, j = 0, num = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    switch(rank){
        case 1:num=10;break;
        case 2:num=1;break;
        case 3:num=110;break;
        case 4:num=0;break;
        case 5:num=780;break;
        case 6:num=13;break;
        case 7:num=12;break;
        case 0:num=-86;break;
    }
    // printf("%d-%d\n",rank,num);
    bitonicSort(rank, &num, size);
    printf("%d-%d\n",rank,num);
    MPI_Finalize();
}