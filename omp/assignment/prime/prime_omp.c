#include<stdio.h>
#include <omp.h>
#define N 10000000


void  main()
{
	

	char arr[N+1]={};
	long i,j,t_count;
	omp_set_nested(1);
	omp_set_num_threads(2);
	#pragma omp parallel private(i,j)
	{
		long count=0;
		#pragma omp for schedule(dynamic)
		for(i=2;i<=N;i++)
		{
			if(arr[i]!='1')
			{
				omp_set_num_threads(2);
				#pragma omp parallel reduction(+:count)
				#pragma omp for schedule(dynamic)
				for(j=i*i;j<=N;j++)			
				{
					if(j%i==0 && arr[j]!='1')
					{
						arr[j]='1';
						count++;
					}
				}
			}
		}
		#pragma omp critical
		{
			t_count+=count;
		}
	}	
	printf("Total primes under %d are %ld\n",N,(N-1)-t_count );

}