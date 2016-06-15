#include <stdio.h>
int main()
{
  int arr[] = {10, 20, 30, 40, 50, 60};
  int *ptr = arr;  // Assigns address of array to ptr
  printf("Value of first element is %d", *ptr);
    return 0;
}
