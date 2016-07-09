#include<stdio.h>


int main(){

  int n =12356,sum=0, i=0;
  for(i=0;n>0;sum+=n%10,n/=10);
  printf("\nSum = %d\n",sum);


}
