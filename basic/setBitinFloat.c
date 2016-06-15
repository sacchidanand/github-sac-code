#include <stdio.h>

int isBitSet(char p)
{
  int k = 0;
  while(p){
    p = p & (p-1);
    k++;
  }
  return k;  
}

unsigned int countSetBitsFloat(float x)
{
  int i = 0 , count = 0;
  int n = sizeof(float)/sizeof(char);
  char *p = (char*) (&x);

  for(i=0;i<n;i++)
  {
    count += isBitSet(*p);
    p++;
  }
  return count;
}

// Driver program to test above function
int main()
{
  float x = 0.15625;
  printf ("Binary representation of %f has %u set bits ", x,
      countSetBitsFloat(x));
  return 0;
}
