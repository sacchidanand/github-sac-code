#define MAXLINE 100
#include<stdio.h>
/*atoi() convert String s to an integer version-1 */
void amain(){
  int n = 0, temp =0;
  int c=0, i=0, j=0, k=0, value =0;
  char s[MAXLINE];
  printf("\n\nEnter number : ");
  while((c =getchar())!='\n'){
        s[i++] = c;
  }
  s[i]='\0';
  value = atoi(s);
  printf("\n\tIntegerValue = %d\n\n", value);
}

/*atoi() convert String s to an integer version-1 */
int atoi(char s[]){
  int i=0, \
        value = 0, \
        n=0;
  
  for(i=0;s[i]==' ';i++); // skip white space

  int sign = (s[i]=='-')?-1:1;
  if(s[i] == '+' || s[i] == '-')
    i++;

  for(n=0;s[i]>='0' && s[i]<='9';i++){
    n = n*10+s[i]-'0';
    printf("\n\t n = %d",n);
  }
  
  printf("\n\t sign = %d",sign);

  return n*sign;
  
/*
 * version-2
  for(i=0;isdigit(s[i]);i++){
    value = value*10 + (s[i]-'0');
  }
*/
}

