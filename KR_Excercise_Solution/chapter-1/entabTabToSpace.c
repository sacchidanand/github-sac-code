#include <stdio.h>

#define TABSTOP 4
#define IN  1
#define OUT 0

int main(void)
{
  int spc, i, c, nspace;
  int state, ntab;

  state = OUT;
  nspace = 0;
  ntab = 0;
  spc = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      state = IN;
      nspace++;
    } else {
      if (state == IN) {
        if (nspace >= TABSTOP) {
          ntab = nspace / TABSTOP;
          spc = nspace % TABSTOP;
          for (i = 0; i < ntab; i++)
            putchar('\t');
          for (i = 0; i < spc; i++)
            putchar(' ');
        } else {
          for (i = 0; i < nspace; i++)
            putchar(' ');
        }
        nspace = 0;
        putchar(c);
        state = OUT;
      } else {
        putchar(c);
      }
    }
  }
  return 0;
}

