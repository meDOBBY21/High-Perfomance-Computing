#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

void main(int argc, char **argv)
{
	// fflush(stdout);
  	int rank= 0, size= 0, a= 0, b= 0, i= 0;
  	MPI_Status status;
  	MPI_Request r= MPI_REQUEST_NULL;
  	MPI_Init(&argc, &argv);
  	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  	MPI_Comm_size(MPI_COMM_WORLD,&size);


  	if(rank==0)
  		a=200;
  	i=1;
  	while(i<size)
  	{
  		if(rank >= i && rank<i*2 && rank<size)
  		{
    		MPI_Recv(&a,1,MPI_INT,rank-i,0,MPI_COMM_WORLD,&status);
  		}
  		if(rank < i && rank<size-i)
  		{
    		MPI_Send(&a,1,MPI_INT,rank+i,0,MPI_COMM_WORLD);
  		}

    	i*=2;
    	
    }
    
  	printf("%d got %d\n",rank,a);
  	MPI_Finalize();
}
