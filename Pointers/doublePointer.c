#include<stdio.h>

int main()
{
  int num = 45 , *ptr , **ptr2ptr ;
  ptr     = &num;
  ptr2ptr = &ptr;

  printf("\nNum = %d",num);
  printf("\n&Num = %d",&num);
  printf("\nptr=%d",ptr);
  printf("\n&ptr=%d",&ptr);
  printf("\n*ptr=%d\n\n",*ptr);
  printf("\nptr2ptr=%d\n\n",ptr2ptr);
  printf("\n&ptr2ptr=%d\n\n",&ptr2ptr);
  printf("\n*ptr2ptr=%d\n\n",*ptr2ptr);
  printf("\n**ptr2ptr=%d\n\n",**ptr2ptr);

  return(0);
}
