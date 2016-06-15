/*************************************************************
 * strrindex will return the rightmost starting position of t in s.
 * I thought this was neat as it's simply the original strindex 
 * function from K&R page 69 with the smallest of changes.  I
 * interpreted the exercise as asking for the index of s at which
 * the final occurence of t begins e.g. for "aaZ" in "aaZZaaaZZaaZa"
 * the answer would be 9.
 * *************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t[]);

int main()
{
  int i;
  char parent[] = "A String with some letters in it.";
  char child[] = "in";

  printf("\nParent : %s \n",parent);
  printf("\nChild : %s \n",child);

  i = strrindex(parent, child);
  printf("Occurence = %d\n\n",i); // In this case, the program will print the number 27.
  return 0;
}

int strrindex(char s[], char t[])
{
  int i, j, k, m = -1;
  for (i = 0; s[i] != '\0'; i++)
  {
    for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
      ;
    if (k > 0 && t[k] == '\0')
      m = i;
  }
  return m;
}

