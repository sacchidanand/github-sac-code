#include<stdio.h>

// 0000 0000 0000 0000 0000 0000 1111 1111
// 1111 1111 0000 0000 0000 0000 0000 0000

int reverse(int x)
{
  int reversed_output;

  char *temp1, *temp2;
  temp1 = (char *)&x;
  temp2 = (char *)&reversed_output;

  *(temp2 + 0) =  *(temp1 + 3);
  *(temp2 + 1) =  *(temp1 + 2);
  *(temp2 + 2) =  *(temp1 + 1);
  *(temp2 + 3) =  *(temp1 + 0);

  return (reversed_output);
}

int main()
{
  int x=255; 
  unsigned output =0 ;
  output = reverse(x);
  printf(" \n ouput %u \n\n", output);
  return 0;
}

