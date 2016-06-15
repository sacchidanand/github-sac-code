#include<stdio.h>

char* itoa(int n){
  char *s = "123";
  return s;
}

int main(){

  int inputNumber=0;
  char *outputString = NULL;
  printf("\n\nEnter Number in integer form: ");
  scanf("%d",&inputNumber);

  outputString = itoa(inputNumber);
  printf("\n\n\tFinal output String is %s\n",outputString);

}
