#include<stdio.h>


int main()
{
  int n = 0;
  char s[2][5] = {"even","odd"};

  scanf("%d",&n);
  
  printf("\nans = %s\n",s[n%2]);
   
return 0;

}
