//FIND THE NEIGHBOUR SUM
//10 Marks for a working program on 2x2
//10 Marks for a working program on perfect squares
//10 Marks for a working program on any number

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

//ptr initially contains the number at the process.
//At the end of the function, it should contain the neighbour sum.
void neighbour_sum(int rank, int size, int rows, int cols, int *ptr)
{
}

int main(int argc, char **argv)
{
  int num= 0, out= 0, rank= -1, seed= -1, size= -1, rows= -1, cols= -1;

  //This part initializes and sets the number in each process to a random integer. Not to be modified.
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  if(argc != 4)
  {
    if(rank == 0)
      printf("ERROR: Provide the seed, rows and cols as the argument\n");
    MPI_Finalize();
    return(0);
  }
  seed= atoi(argv[1]);
  srand(seed+rank);
  num= rand() % 1000;
  if(rank % 2 == 0)
    num*= -1;
  rows= atoi(argv[2]);
  cols= atoi(argv[3]);
  if(rows*cols != size)
  {
    if(rank == 0)
      printf("ERROR: Rows*Cols is not same as number of processes\n");
    MPI_Finalize();
    return(0);
  }

  //num= rank;
  printf("%d: Before Neighbour sum, num= %d, rows= %d, cols= %d\n",rank,num,rows,cols);
  neighbour_sum(rank,size,rows,cols,&num);
  printf("%d: After Neighbour sum, num= %d\n",rank,num);

  MPI_Finalize();
}
