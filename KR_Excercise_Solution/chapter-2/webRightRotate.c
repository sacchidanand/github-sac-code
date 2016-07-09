#include<stdio.h>

unsigned rightrot(unsigned x, int n);

void displayInBits(unsigned n, size_t size){
  int i =0;
  //printf("\n\t Size = %d\n\n",size);
  printf("\n");

  for(i=size*8-1; i>=0; i--){
    ((n>>i) & 1) ? putchar('1'): putchar('0');
    if(!(i%4))
      printf(" ");
  }
  printf("\n\n");
}

unsigned getbits(unsigned n, int p, int x){
  //return ((n>> (p-x+1)));
  //  //return  ((~(~0<<x)));
  //    //return (~(~0<<x)?~(~0<<x):(~0));
  return ((n>>(p+1-x)) & (~(~0<<x)?~(~0<<x):(~0)));
}

unsigned int rightrot(unsigned int x, int n) {
  /*  
  int m, i;
  for(i=0; i < n; i++) {
    m = getbits(x, 0, 1);
    m <<= (sizeof(m)*8-1);
    x >>= 1;
    x |= m;
  }
  */
  
  int s = sizeof(x)*8;
  return (x>>n | x<<(s-n));
}

/*
unsigned rightrot(unsigned x, int n){
  return x >> n | ((x & (~(~0 << n))) << (8 - n));
}
*/

int main(void)
{
  unsigned n = 0x12345678, pos=5;

  //printf("\n Enter Number:");
  //scanf("%d",&n);

  printf("\n Enter position:");
  scanf("%d",&pos);

  displayInBits(n, sizeof(n));
  n = rightrot(n, pos);

  displayInBits(n, sizeof(n));
  return 0;
}


