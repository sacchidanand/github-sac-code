#include<stdio.h>
int main()
{
  int i=0;
  //Array declaration by initializing it with more
  //    elements than specified size.
  int arr[2] = {10, 20, 30, 40, 50};
  for(i=0;i<5;i++)
  printf("%d\n",arr[i]);

  return 0;
}
