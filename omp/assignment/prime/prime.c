#include<stdio.h>

#define N 10000000


void  main()
{
	

	char arr[N+1]={};
	long count=0,i,j,k;


	for(i=2;i<=N;i+=1)
		if(arr[i]!='1')
			for(j=i*i;j<=N;j+=2)			
				if(j%i==0 && arr[j]!='1')
				{
					arr[j]='1';
					count++;
				}
	printf("Total primes under %d are %ld\n",N,(N-1)-count);

}