#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>

/*Note: '^' is XOR operator.
		'&' (Single AND) is Binary AND.*/


void one_to_all_Bcast_HC(int rank,int d,int* msg,int src)
{
	MPI_Status status;
	int i,virtual_rank,mask,destination,source,mask_maker;
	virtual_rank=rank^src;

	mask=(int)pow(2,d)-1;

	for(i=d-1;i>=0;i--)
	{
		mask_maker=(int)pow(2,i);
		mask=mask^mask_maker;
		if((virtual_rank & mask)==0)
		{
			if((virtual_rank & mask_maker)!=0)
			{
				source=virtual_rank^mask_maker;
				MPI_Recv(msg,1,MPI_INT,(source^src),1,MPI_COMM_WORLD,&status);
			}
			else
			{
				destination=virtual_rank ^ mask_maker;
				MPI_Send(msg,1,MPI_INT,(destination^src),1,MPI_COMM_WORLD);
				
			}
		}	
	}
}


int main(int argc, char **argv)
{
	int rank,size,num=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0)
		num=(rand()%10+1);

	printf("This is num before Bcast: \t %d for %d\n",num,rank);
	
	one_to_all_Bcast_HC(rank,3,&num,0);

	printf("This is num after Bcast: \t %d for %d \n",num,rank);

	MPI_Finalize();
	return 0;
}