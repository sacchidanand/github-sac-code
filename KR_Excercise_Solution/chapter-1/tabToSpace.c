#include <stdio.h>

#define TAB 5

int main(void)
{
  int c, x, r;
  x = 0;

  while((c = getchar())!= EOF) {
    if(c == '\n') {
      putchar(c);
      x = 0;
    }
    else if (c == '\t') {
      r = TAB - x % TAB;
      while(r-- != 0) {
        putchar(' ');
        x++;
      }
    }
    else {
      putchar(c);
      x++;
    }
  }
  return 0;
}


