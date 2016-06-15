#include<stdlib.h>
#include<stdio.h>

#define UNINIT -200

/*partition*/
int partition(int *a, int start, int end){
  int pivot = a[end], i= UNINIT, temp = 0;
  int pIndex = start;

  for(i=start; i<end; i++){
    if(a[i] <= pivot){
      //swap(&a[i], &a[pIndex]);
      
      temp = a[i];
      a[i] = a[pIndex];
      a[pIndex] = temp;
      pIndex++;
    }
  }
      //swap(&a[end], &a[pIndex]);
  
  temp = a[end];
  a[end] = a[pIndex];
  a[pIndex] = temp;
  
  return pIndex;
}

/*Recursive quick sort*/
void quickSort(int *a, int start, int end){
  int pIndex = 0;
  if(start>=end)
    return;
  pIndex = partition(a, start, end);
  quickSort(a, start, pIndex-1);
  quickSort(a, pIndex+1, end);
}

void printArray(int *a, int size){
  int i=0;
  printf("\n\n\tPrinting Array \n\n");
  for(i=0; i<size; i++){
    printf("%d->",a[i]);
  }

}

int main(){
  int a[] = {36, 28, 12,42, 15, 33, 89, 21};
  int size = sizeof(a)/sizeof(a[0]);
  printf("\nArray Size = %d", size);
  printArray(a,size);
  getchar();
  quickSort(a,0,size-1);
  printArray(a,size);
  printf("\nExiting Successfully !\n");
return 0;
}

