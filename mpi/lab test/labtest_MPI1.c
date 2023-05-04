//Implement One-to-all Broadcast in ring of p processes, for any p > 2 and from any source.
//implementation that works for p = power of 2, from any source, 10 Marks
//implementation that works for any p, from any source, 10 Marks

#include <stdio.h>
#include <mpi.h>

void One_to_all_bcast(void *buf, int count, MPI_Datatype dp, int src, MPI_Comm comm)
{
  MPI_Status status;
  int i,rank,size,virtual_rank;
  MPI_Comm_rank(comm,&rank);            //Getting rank of each process
  MPI_Comm_size(comm,&size);            //Getting the total processes participating
  virtual_rank=(rank-src+size)%size;    //Calculating the Virtual_rank in order to broadcast through any source

  i=1;                                  //Keeping i as 1 for future calculations
  while(i<size)                         //taking i till last process
  {
    /*Checking who should recieve the buf:
            i.e.,
            i=1(1st iteration):virtual_rank-1 will recieve buf because only it is in between [1,2)  
            i=2(2nd iteration):virtual_ranks-2,3 will recieve buf,between [2,4)
           
            ..................................................................
            so on  

        we added "virtual_rank<size" for non 2 power processes
    */

    if(virtual_rank >= i && virtual_rank<i*2 && virtual_rank<size)    
      MPI_Recv(buf,count,dp,(rank-i+size)%size,0,comm,&status);
                              //Here instead of take from virtual_rank we directly take from rank

    /*Checking who should send the buf:
        i.e.,
            i=1(1st iteration):virtual_rank-0 will recieve buf because only it is in between [0,1)  
            i=2(2nd iteration):virtual_ranks-0,1 will recieve buf,between [0,2)
            ..................................................................
            so on  

        we added "virtual_rank<size" for non 2 power processes
    */

    if(virtual_rank < i && virtual_rank<size-i)
      MPI_Send(buf,count,dp,(rank+i)%size,0,comm);
                            //Here instead of sending to virtual_rank we directly send to rank

    i*=2;  //In every iteration we have double the processes with data compared to previous iteration,
           //So we make i double every iteration
  }
}

int main(int argc, char **argv)
{
  int rank= 0, size= 0;
  int arr[10]= {};
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  if(rank == 9)
    for(int i= 0; i < 10; i++)
      arr[i]= 3*i;

  One_to_all_bcast(arr,10,MPI_INT,9,MPI_COMM_WORLD);
  
  printf("%d got %d\n",rank,arr[5]);
  MPI_Finalize();
}
