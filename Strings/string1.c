//#include<stdlib.h>
#include<stdio.h>
//This C program compiles fine as index out of bound
//is not checked in C.
int main()
{
  int arr[2];

  printf("%d ", arr[3]);
  printf("%d ", arr[-2]);

  return 0;
}

