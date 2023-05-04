#include<stdio.h>
#include<omp.h>

#define N 10
void main()
{
	int arr[N],id;
	omp_set_num_threads(N);
	#pragma omp parallel
	{
		id=omp_get_thread_num();
		arr[id]=id;
		printf("arr[%d] : %d\n",id,id);
		printf("%d",omp_get_num_devices());
	}

}
