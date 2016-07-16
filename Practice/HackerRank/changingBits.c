/*
   Changing Bits
   by HackerRank

   Let A and B be two N bit numbers (MSB to the left).
   You are given initial values for A and B, and you have to write a program which processes three kinds of queries:

   set_a idx x: Set A[idx] to x, where 0 <= idx < N, where A[idx] is idx'th least significant bit of A.
   set_b idx x: Set B[idx] to x, where 0 <= idx < N, where B[idx] is idx'th least significant bit of B.
   get_c idx: Print C[idx], where C=A+B, and 0<=idx 
   .......................................................................................................................

#Input Format:

First line of input contains two integers N and Q consecutively (1 <= N <= 100000, 1<= Q <= 500000). Second line is an N-bit binary number which denotes initial value of A, and the third line is an N-bit binary number denoting initial value of B. Q lines follow, each containing a query as described above.
.......................................................................................................................

#Output Format

For each query of the type get_c, output a single digit 0 or 1. Output must be placed in a single line.
.......................................................................................................................

Sample Input

5 5  
00000  
11111  
set_a 0 1  
get_c 5  
get_c 1  
set_b 2 0  
get_c 5

Sample Output

100  
.......................................................................................................................

Explanation

set_a 0 1 sets 00000 to 00001
C = A + B = 00001 + 11111 = 100000, so get_c[5] = 1
from the above computation get_c[1] = 0
set_b 2 0 sets 11111 to 11011
C = A + B = 00001 + 11011 = 011100, so get_c[5] = 0

The output is hence concatenation of 1, 0 and 0 = 100
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAXBITS 32
#define MAXLEN 15

void setBit(int *n, int idx, int x); 
void getBit(int *n, int *x);
int binaryToInt(char *a, int len);

int main()
{
  int numberOfBits, numberOfLines;
  char a[MAXBITS], b[MAXBITS], inputLine[MAXLEN], outputLine[MAXLEN];
  int na=0, nb=0, idx=0, x=0, outputIndex = 0, i=0, res = 0;

  scanf("%d %d",&numberOfBits, &numberOfLines);

  if(0 == numberOfBits)
  {
    printf("Invalid number of bits");
    exit(0);
  }

  scanf("%s", a); 
  scanf("%s", b); 

  na = binaryToInt(a, numberOfBits);
  nb = binaryToInt(b, numberOfBits);

  for(i=0; i< numberOfLines; i++)
  {
    scanf("%s %d", inputLine, &idx);

    if('s'== inputLine[0])
    {
      scanf(" %d", &x);
      (inputLine[4]=='a')?(setBit(&na, idx, x)):((inputLine[4]=='b')?setBit(&nb, idx, x): printf("Error"));
    }
    else if('g' == inputLine[0])
    {
      res = na + nb;
      (inputLine[4]=='c')?(getBit(&res, &idx)):printf("Error");
      outputLine[outputIndex++] = idx + 48;
    }
    else
    {
      printf("Invalid number of bits");
      exit(0);
    }

  }//for-end

  outputLine[outputIndex] ='\0';  
  printf("%s\n", outputLine);

  return 0;
}

void getBit(int *n, int *x)
{
  *x = (*n>>(*x)) & 1;
}

void setBit(int *n, int idx, int x)
{
  if(1 == x)
  {
    *n |= ((~((~0)<<1))<<idx);
  }
  else if(0 == x)
  {
    *n &= ~((~((~0)<<1))<<idx);
  }
  else{
    exit(0);
  }
}

int binaryToInt(char *a, int len)
{
  int i=0, sum=0;

  for(i=0; i<len; i++)
  {
    sum = sum + ((a[len-i-1]-48)*(1<<i));
  }
  return sum;
}


