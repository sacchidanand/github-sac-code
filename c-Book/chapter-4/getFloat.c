#include <stdio.h>
#include <ctype.h>

#define STR_MAX 1000;

int getfloat(double*);

int main()
{
  double flt = 0;
  int ret = 0;
  ret = getfloat(&flt);
  printf ("Return: %f\n", flt);
  return 0;
}

#define BUFSIZE 100

char buf[BUFSIZE];      /* Buffer for ungetch. */
int bufp = 0;           /* Next free position in buf. */

int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
  if (bufp >= BUFSIZE) {
    printf("Ungetch: Too many characters.\n");
  } else {
    buf[bufp++] = c;
  }
}

int getfloat(double *pn)
{
  int c, sign;
  int dec, pos = 0;
  while (isspace(c = getch()));

  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); /* it is not a number */
    return 0;
  }

  sign = (c == '-') ? -1 : 1;

  if (c == '+' || c == '-') {
    c = getch();
  }

  /* 46 is the ascii code for "." */
  for (*pn = 0; isdigit(c) || c == 46 ; c = getch()) {
    if (c != 46) {
      pos++;
      *pn = 10 * *pn + (c - '0');
    } else if (c == 46) {
      dec = pos;
    }
  }

  dec = pos - dec;
  for ( ; dec != 0; dec--) {
    *pn /= 10.0;
  }

  *pn *= sign;

  if (c != EOF) {
    ungetch(c);
  }

  return c;
}

