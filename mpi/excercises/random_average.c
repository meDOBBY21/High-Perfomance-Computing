#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char  **argv)
{
    MPI_Status status;
    int rank,size,i,*arr,k,*data,sum;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    srand(rank * time(NULL));

    if(rank==0)
    {
        data=(int*)malloc(size*sizeof(int));
        for(i=1;i<size;i++)
            MPI_Recv(&data[i],1,MPI_INT,i,1,MPI_COMM_WORLD,&status);
        for(i=1;i<size;i++)
            printf("%d ",data[i]);
        printf("\n");
        
    }
    else
    {
        k=rand()%10+1;
        printf("Rank:%d k:%d\n",rank,k);
        MPI_Send(&k,1,MPI_INT,0,1,MPI_COMM_WORLD);
    }

    // if(rank!=0)
    // {
    //     arr=(int*)malloc(k*sizeof(int));
    //     for(i=0;i<k;i++)
    //        arr[i]=i;
    //     for(i=1;i<k;i++)
    //         printf("%d ",arr[i]);
    //     printf(":%d\n",rank);
    //     MPI_Send(&arr,k,MPI_INT,0,1,MPI_COMM_WORLD);
    // }
    // else
    // {
    //     for(i=1;i<size;i++)
    //     {
    //         sum=0;
    //         arr=(int*)malloc(data[i]*sizeof(int));
    //         MPI_Recv(&arr,data[i],MPI_INT,i,1,MPI_COMM_WORLD,&status);
    //         for(int j=0;j<data[0];j++)
    //             sum+=arr[j];
    //         sum=sum/data[i];
    //         printf("%d - %d",i,sum);
    //     }
    // }

    free(arr);
    return 0;
}

