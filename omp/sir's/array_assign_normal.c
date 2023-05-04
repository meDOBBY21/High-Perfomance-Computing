#include<stdio.h>

#define N 10

void main()
{
	int i,arr[N];
	
	for(i=0;i<N;i++)
	{
		arr[i]=i;
		printf("arr[%d] : %d\n",i,i);
	}
	
}
