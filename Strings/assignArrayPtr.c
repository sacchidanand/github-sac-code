//IInd program to show that array and pointers are different
#include <stdio.h>
int main()
{
  int arr[] = {10, 20}, x = 10;
  int *ptr = &x; // This is fine
  arr = &x;  // Compiler Error
  return 0;
}
