#include<stdio.h>
#include<stdlib.h>

int sum(int a, int b)
{
  return (a+b);
}

int main()
{

  int a=10, b=20;
  int (*sum_cb)(int,int);
  sum_cb=sum;

  printf("\n sum = %d\n", sum(a,b));
  printf("\n sum_cb = %d\n", sum_cb(a,b));

  printf("\n address in %%p sum_cb = %p\n", sum_cb);
  printf("\n address in %%x sum_cb = %x\n", sum_cb);

return 0;
}
