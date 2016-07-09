#include<stdio.h>
/*
0   0 ff

1   0 ff00

2   0 ff0000

3   0 ff000000

   0 4278190080
*/

void reverse(unsigned int *a, unsigned int *b)
{
  unsigned int temp=0, i=0, c=0; 

  for(i=0;i<4;i++)
  {
   *b = (*b)<<8;
   temp = *a;
   temp = temp>>8; 
   temp = temp<<8;
   c = *a - temp;
   *b+=c;
   *a = (*a)>>8;
   printf("\n %x %x\n ",*a,*b);
  }
   printf("\n %u %u\n ",*a,*b);
}

int main()
{
  unsigned int a=255, b = 0;
 
  printf("\n\nBefore : a = %u, b=%u",a,b);
  reverse(&a,&b); 
  printf("\n\nAfter  : a = %u, b=%u",a,b);
 
 /*
  char *t1, *t2;
  t1 = (char*)&b;
  t2 = (char*)&a;
  printf("\n\nBefore : a = %u, b=%u",a,b);
  t1[0] = t2[3];
  t1[1] = t2[2];
  t1[2] = t2[1];
  t1[3] = t2[0];
  printf("\n\nAfter : a = %u, b=%u", a,b);
*/

  printf("\n\n");
  return 0;
}


