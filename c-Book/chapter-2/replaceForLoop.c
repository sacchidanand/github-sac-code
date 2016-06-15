/*
   for(i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
   s[i] = c;
   */


#include <stdio.h>
#define MAXLINE 1000 /* maximum line size */

int main(void) {
  int i, c;
  char line[MAXLINE]; /* current line */

  /* If the comparison of some of then is false then will be 0, as consequence
   * the result of the multiplication will be 0, if all are true then the
   * result will be a non zero, and the result of non-zero multiplication
   * is a non-zero element that is evalutes as true. For the || operator
   * we can use "+".
   */
  for (i = 0; (i < MAXLINE-1) * ( (c=getchar()) != '\n') * (c != EOF) ; ++i)
    line[i] = c;
  line[i] = c;
  printf("%s\n", line);
  return 0;
}

