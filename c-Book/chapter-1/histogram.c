#include <stdio.h>

/* Prints a histogram of the length of words in the input                    */
/*****************************************************************************/
/* This program doesn't count the last word if the input didn't finished in  */
/* a blank. Fortunately in the bast majority of cases the last character is  */
/* a new line character                                                      */
/*****************************************************************************/
/* Vertical version                                                          */

int main()
{
  int len_freq[11];          /* Stores the freq of each length             */
  int length, height;        /* Stores actual length and highest freq      */
  int c, i, k;

  length = height = 0;       /* Start with current length and highest      */
  /* frequency being 0                          */
  for(i = 0; i <= 10; ++i)   /* Initialise each element of the len_freq    */
    len_freq[i] = 0;       /* array to be 0                              */

  /* Reads the input storing each frequency                                */
  while((c = getchar()) != '#'){
    if(c != ' ' && c != '\n' && c != '\t')
      ++length;
    else if(length != 0){
      if(length <= 10){
        ++len_freq[length-1];
        if(height < len_freq[length-1])
          height = len_freq[length-1];
      }
      else{
        ++len_freq[10];
        if(height < len_freq[10])
          height = len_freq[10];
      }
      length = 0;
    }
  }

  /* Creates the histogram                                                 */
  for(i = height; i > 0; --i){
    printf("%2d|", i);
    for(k = 0; k <= 10; ++k){
      if(len_freq[k] >= i)
        printf("   #");
      else
        printf("    ");
    }
    printf("\n");
  }

  printf("  +");
  for(i = 0; i <= 10; ++i)
    printf("----");
  printf("\n   ");

  /* Print the x-axis values */
  for(i = 0; i <= 10; ++i){
    if(i < 10)
      printf("%4d", i+1);
    else
      printf(" +10");
  }
  printf("\n");

  return 0;
}

