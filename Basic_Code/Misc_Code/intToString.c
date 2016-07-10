#include<stdio.h>


int main()
{

  char s[100];
  int n=1234, ret = 0;

  ret = sprintf(s,"%d",n);
  printf("\nret =%d, string s = %s\n", ret,s);

return 0;
}
