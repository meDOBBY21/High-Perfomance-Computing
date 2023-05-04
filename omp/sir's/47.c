	#include <stdio.h>
#include <omp.h>
#include <limits.h>

//Find max of new value n and the existing reduced value r
int mymax(int r, int n)
{
  printf("%d: r= %d, n= %d\n",omp_get_thread_num(),r,n);
  if(r > n)
    return(r);
  return(n);
}

int main()
{
  int N= 10, max= 110;

  #pragma omp declare reduction(mm:int:omp_out=mymax(omp_out,omp_in)) initializer(omp_priv=INT_MAX-1)
  #pragma omp parallel reduction(mm:max) num_threads(4)
  {
    #pragma omp for
    for(int i= 0; i < N; i++){
      if(i > max)
        max= i;
      if(i==0)
        max=INT_MAX;
    }
  }
  printf("Calculated max= %d\n",max);
}
