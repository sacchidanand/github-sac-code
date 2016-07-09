#include <stdio.h>

/* Creates a histogram with the frequency of the characters in the input     */
/* Vertical version                                                          */

int main()
{
  int len_freq[94];
  int heigth;
  int c, i, k;

  heigth = 0;

  for(i = 0; i <= 93; ++i)
    len_freq[i] = 0;

  /*Calculating frequecies*/
  while((c = getchar()) != EOF)
  {
    if(33 <= c && c <= 126)
    {
      ++len_freq[c-33];
      if(len_freq[c-33] >= heigth)
        heigth = len_freq[c-33];
    }
  }

  /*Printing y-axis value in histogram*/
  for(i = heigth; i > 0; --i)
  {
    printf("%4d|", i);

    for(k = 0; k <= 93; ++k)
    {
      if(len_freq[k] >= i)
        printf("#");
      else
        printf(" ");
    }
    printf("\n");
  }

  printf("    +");
  for(i = 0; i <= 93; ++i)
    printf("-");
  printf("\n     ");

  /* Print x-axis values */
  for(i = 0; i <= 93; ++i){
    printf("%c", i+33);
  }
  printf("\n");

  /* Print x-axis values in integer ASCII values*/
  for(i = 0; i <= 93; ++i){
    printf("%d", i+33);
  }
  printf("\n");
  
  return 0;
}


