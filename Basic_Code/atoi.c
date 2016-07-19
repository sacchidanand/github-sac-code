#include<stdio.h>
#include<stdlib.h>

#define MAXLINE 100

/*atoi() convert String s to an integer version-1 */
main()
{
  int n = 0, temp =0;
  int c=0, i=0, j=0, k=0, value =0;
  char s[MAXLINE];
  printf("\n\nEnter number : ");

  //accept input as string
  while((c =getchar())!='\n'){
        s[i++] = c;
  }
  s[i]='\0';

  //convert string to integer
  for(i=0; isdigit(s[i]); i++){
    value = value*10 + (s[i]-'0');
  }

  printf("\nvalue = %d\n\n", value);

}
