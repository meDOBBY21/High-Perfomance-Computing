#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


void all_to_all_BCast(int rank,int p,int msg,int* result)
{
	MPI_Status status;

	int l,r,i,temp,index,j,row,col,u,d,root_p;

	root_p=(int)pow(p,(.5));

	row=rank/root_p;
	col=rank%root_p;

	l=(col-1+p)%p+(row*root_p) ;
	r=(col+1)%p+(row*root_p);
	result[rank]=msg;
	for(i=0;i<root_p-1;i++)
	{
		MPI_Send(&msg,1,MPI_INT,r,1,MPI_COMM_WORLD);
		MPI_Recv(&msg,1,MPI_INT,l,1,MPI_COMM_WORLD,&status);
		result[(l-i+p)%p]=msg;	
	}

	u=col+((row+1)%root_p)*root_p;
	d=col+((row-1+root_p)%root_p)*root_p;

	buff=result;
	for(i=1;i<root_p-1;i++)
	{
		MPI_Send(&buff,)
	}

}

int main(int argc, char **argv)
{
	int i,rank,size,num,result[8]={};
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	num=rank+1;
	printf("This is num before Bcast for %d : %d\n",rank,num);

	all_to_all_BCast(rank,size,num,result);

	printf("This is result after Bcast for %d: ",rank);
	for(i=0;i<size;i++)
		printf("%d ",result[i]);
	printf("\n");
	MPI_Finalize();
	return 0;
}f            