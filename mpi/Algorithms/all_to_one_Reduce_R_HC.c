#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define L 8

/*
	When I do for rank=msg
	i.e., 
		0 has 0
		1 has 1
		2 has 2
		. ... .
		. ... .
		7 has 7

	I should get 0,8,16,24,32,40,48,56 in destination.

*/

void all_to_one_reduce(int rank,int p,int* arr,int len,int dest)
{
	MPI_Status status;
	int i,virtual_rank,result[len],d,mask=0,j=0,destination,source,mask_maker;

	virtual_rank=rank^dest;
	for(i=0;i<len;i++)
		result[i]=arr[i];
	d=log(p);
	for(i=0;i<d;i++)
	{
		mask_maker=(int)pow(2,i);
		if((virtual_rank & mask)==0)
		{
			if((virtual_rank & mask_maker)==0)
			{
				source=virtual_rank^mask_maker;
				MPI_Recv(arr,len,MPI_INT,(source^dest),1,MPI_COMM_WORLD,&status);
				for(j=0;j<len;j++)
					result[j]+=arr[j];
			}
			else
			{
				destination=virtual_rank ^ mask_maker;
				MPI_Send(result,len,MPI_INT,(destination^dest),1,MPI_COMM_WORLD);
				
			}
		}	
		mask=mask^mask_maker;
	}
	for(i=0;i<len;i++)
		result[i]+=arr[i];
		
	printf("In Function for %d- ",rank);
	for(i=0;i<len;i++)
		printf("%d ",result[i]);
	printf("\n");

}

int main(int argc, char **argv)
{
	int i,rank,size,num[L];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	for(i=0;i<L;i++)
		num[i]=i;

	// printf("This is num before Bcast for %d :",rank);
	// for(i=0;i<L;i++)
	// 	printf("%d ",num[i]);
	// printf("\n");
	all_to_one_reduce(rank,size,num,L,7);

	// printf("This is num after Bcast for %d:",rank);
	// for(i=0;i<L;i++)
	// 	printf("%d ",num[i]);
	// printf("\n");
	MPI_Finalize();
	return 0;
}