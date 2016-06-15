#include <stdio.h>
#include <string.h>

void reverse(char *p, char *q)
{
  if(q + 1 == p || p == q)
    return;
  int c;
  c = *p;
  *p = *q;
  *q = c;
  reverse(p+1, q-1);
}

int main()
{
  char str[] = "abc";
  reverse(str, str + strlen(str) - 1 );
  printf("%s\n", str);
  return 0;
}

