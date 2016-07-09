#include <ctype.h>
#include <stdio.h>
#define BUFFERLENGTH 100
int getch(void);
void ungetch(int);

int buf[BUFFERLENGTH];
int nfp = 0;

void viewbuffer(void)
{
  int i;
  printf("\nbuffer:\n");
  for(i = nfp - 1; i >= 0; i--)
    printf("%d\n", buf[i]);
}

int getch(void)
{
  return (nfp > 0) ? buf[--nfp] : getchar();
}

void ungetch(int c)
{
  if(nfp < BUFFERLENGTH)
    buf[nfp++] = c;
  else
    printf("error: ungetch buffer overflow\n");
}

int getint(int *pn)
{
  int c, sign;
  while(isspace(c = getch()));
  if(!isdigit(c) && c != EOF && c != '+' && c != '-')
  {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if(c == '+' || c == '-') // If character read is + or -
  {
    c = getch(); // Read next character
    if(!isdigit(c)) // If it is not a digit
    {
      ungetch(sign == -1 ? '-' : '+'); // pushback on to the buffer the operator that was previously read
      return 0;
    }
  } 
  for(*pn = 0; isdigit(c); c = getch())
    *pn = *pn * 10 + (c - '0');
  *pn *= sign;
  if(c != EOF)
    ungetch(c);
  return c;
}

int main()
{
  int x, retval;
  int* px;
  px = &x;
  retval = getint(px);
  printf("retval = %d, x = %d\n", retval, x);
  viewbuffer();
  return 0;
}

