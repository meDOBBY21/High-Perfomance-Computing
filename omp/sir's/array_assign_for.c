#include<stdio.h>
#include<omp.h>
#define N 10000

void main()
{
	omp_set_num_threads(N);
	int arr[N][N;
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<N;i++)
		{
			arr[i]=i;
			printf("arr[%d] : %d\n",i,i);
		}
	}
}

