#include <stdio.h>
#include <mpi.h>

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

void even_odd_T_S(int p, int rank, int* num)
{
    MPI_Status status;
    int i, partner, buff;
    for (i = 0; i < p; i++)
    {
        if (i % 2 == 0)
        {
            if (rank % 2 == 0 && rank < p - 1)
            {
                partner = rank + 1;
                MPI_Send(num, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
                MPI_Recv(&buff, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
                compare_exchange_min(num, &buff);
            }
            else if (rank % 2 != 0)
            {
                partner = rank - 1;
                MPI_Send(num, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
                MPI_Recv(&buff, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
                compare_exchange_max(num, &buff);
            }
        }
        else
        {
            if (rank > 0)
            {
                if (rank % 2 != 0 && rank < p - 1)
                {
                    partner = rank + 1;
                    MPI_Send(num, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
                    MPI_Recv(&buff, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
                    compare_exchange_min(num, &buff);
                }
                else if (rank % 2 == 0)
                {
                    partner = rank - 1;
                    MPI_Send(num, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
                    MPI_Recv(&buff, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
                    compare_exchange_max(num, &buff);
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    int rank = 0, size = 0, i = 0, j = 0,num=0;

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
    printf("%d-%d\n",rank,num);
    even_odd_T_S(size,rank,&num);
    MPI_Barrier(MPI_COMM_WORLD);
    // if(rank=0){
    //     printf("\n");}
    printf("%d-%d\n",rank,num);
    MPI_Finalize();
    return 0;
}
