#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>

int sum1(int total, ...)
{
  int i=0, sum=0;
  va_list valist;

  va_start(valist, total);
    
  for(i=0; i<total; i++)
  { 
    sum += va_arg(valist, int);
  //printf("sum = %d \t total=%d\n",sum, total);
  }

  va_end(valist);
  return sum;
}

int main()
{
  int sum = sum1(4, 1,2,3,4);
  printf("sum = %d\n",sum);
  
  sum = sum1(3, 1,2,3);
  printf("sum = %d\n",sum);

  return 0;
}
