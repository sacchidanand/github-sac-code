#include<stdio.h>

int main(){
  unsigned int a,b=0,ch,i,temp;
  scanf("%u",&temp);
  a = temp;
  for(i=1;i<=4;i++){
    b = b << 8;
    temp = a;
    a = a >> 8;
    a = a << 8;
    ch = temp - a;  // Single byte is separated here
    b = b + ch;
    printf("\n%x, %x",a,b);
    a = a >> 8;
  }
  printf("\n\n%u",b);
  return 0;
}
