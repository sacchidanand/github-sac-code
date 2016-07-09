#include<stdio.h>
#include<string.h>

char *reverse(char*s){
  unsigned int len = strlen(s), i= 0, j=0, temp =0;
  for(i=0, j=len-1; i<j; i++,j--){
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    printf("\n s[i]=%c s[j]=%c", s[i], s[j]);
  }
  return s;
}

char* itoa(int n){
  char t[100] = "";
  char *s = t;
  int i=0, sign=0;

  if((sign=n)<0)
    n = n*-1;

  printf("\n\n Inside itoa\n\n");
  for(i=0;n>0;i++){
    printf("\n s=%s, n=%d", s, n);
    s[i] = (n%10) + '0';
    n = n/10;
  }
  
  if(sign<0)
    s[i++] = '-';

  s[i]='\0';
  printf("\n\n Before value is : %s", s);

  s = reverse(s);
  printf("\n\n After value is : %s", s);
  return s;
}

int main(){

  int inputNumber=0;
  char *outputString = NULL;
  printf("\n\nEnter Number in integer form: ");
  scanf("%d",&inputNumber);

  outputString = itoa(inputNumber);
  printf("\n\n\tFinal output String is %s\n",outputString);

  return 0;
}
