#include <stdio.h>

int any(char s1[],char s2[]);

int main() {
  char s1[] = "hello world";
  char s2[] = "pjwyh";
  printf("%d\n", any(s1,s2));
  return 0;
}

int any(char s1[], char s2[])
{
  int i, j;

  for(i = 0; s1[i] != '\0'; i++) {    /* for each s1[i] */
    for(j = 0; s2[j] != '\0'; j++) {  /* for each s2[j] */
      if(s1[i] == s2[j])    /* match found? */
        return i;   /* no need for further code */
    }
  }
  return -1;          /* no match */
}

/*

   int
   any(char s1[], char s2[]) {
   int i, j;
   int ret = -1;
   for(j=0; s2[j] != '\0'; j++)
   for(i=0; s1[i] != '\0'; i++)
   if(s1[i] == s2[j])
   if(ret<0)
   ret = i;
   else if(i<ret)
   ret = i;
   return ret;
   }
   */
