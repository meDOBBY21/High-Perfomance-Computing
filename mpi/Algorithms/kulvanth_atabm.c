#include <stdio.h>
#include <unistd.h>
#include <mpi.h>
#include <math.h>

void all_to_all_bcast(int my_id,int root_p,int my_msg,int *result){

	//printf("entering fun\n");
	MPI_Status status;
	int left , right , up , down , row , col , i , j , p , index = 0 , temp[root_p],x=root_p-1;

	row = my_id/root_p;
	col = my_id%root_p;
	p = root_p * root_p;

	left = row*root_p + (col-1+root_p)%root_p;
	right = row*root_p + (col+1)%root_p;
	index = left;

	result[my_id] = my_msg;

	for(i=0;i<=root_p-1;i++){

		MPI_Send(&my_msg,1,MPI_INT,right,0,MPI_COMM_WORLD);

		MPI_Recv(&my_msg,1,MPI_INT,left,0,MPI_COMM_WORLD,&status);

		result[index] = my_msg;
		printf("%d is index of result and %d is index of temp\n",index,index%root_p);
		temp[index%root_p] = my_msg;
		index = index - 1;
		x--;
	}
	
	if(my_id==2)
	for(int p=0;p<root_p;p++)
		printf("temp of %d is %d\n",p,temp[p]);
	
	up = ( (row+1) % root_p )*root_p + col;
	down = ( (row - 1 + root_p) % root_p )*root_p + col;
	
	for(i=0;i<=root_p-1;i++){
		
		MPI_Send(&temp,root_p,MPI_INT,up,0,MPI_COMM_WORLD);
		
		MPI_Recv(temp,root_p,MPI_INT,down,0,MPI_COMM_WORLD,&status);
		
		for(int k=0;k<root_p;k++){

			index = ((row - i - 1 + root_p)%root_p)*root_p + k;
			result[index] = temp[k];
		}	 
	}

}

int main(int argc,char **argv)
{

  int rank= 0, size = 0, d, msg ;
  
  //MPI_Request r= MPI_REQUEST_NULL;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  int root_p = (int)sqrt(size);
  int result [size] ; 

  all_to_all_bcast(rank,root_p,rank,result);

  if(rank==15)
  	for(int i=0;i<size;i++)
	  printf("rank %d got %d at index %d\n",rank,result[i],i);

  MPI_Finalize();
  return 0;
}
