#include <stdio.h>
#include <limits.h>
#define MAXLEN 100

char * itoa(int n, char *s)
{
  static int i = 0;
  if(n < 0)
  {
    s[i++] = '-';
    n = -n;
  }
  if(n/10)
    itoa(n/10, s);
  s[i++] = n%10 + '0';
  s[i] = '\0';
}

int main()
{
  int n = INT_MIN + 1;
  char str[MAXLEN];
  itoa(n, str);
  printf("%s\n", str);
  return 0;
}


