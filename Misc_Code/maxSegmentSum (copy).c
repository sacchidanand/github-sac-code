#include<stdio.h>
#include<stdlib.h>


int MaxSegSum(int a[], int n){

  int sum = a[0], temp =0, length =0, i =0;

  for(length =0 ; length<n; length++)
  { 
    if(sum < a[length]){
      sum = a[length];
    }

    temp =0;
    for(i=0; i+length<n; i++){
      temp = temp + a[i];
    }

    if(sum < temp){
      sum =temp;
    }

  }
  return sum;
}

int main(){
  int a[] = {3,-2,5,-1};
  int sum  = MaxSegSum(a,4);
  int size  = sizeof(a)/sizeof(a[0]);

  for(i=0;i<size;i++)
    printf("%d ",a[i]);


  printf("\n\nSum =%d\n\n", sum);
  return 0;
}
