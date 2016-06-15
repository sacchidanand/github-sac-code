#include<stdio.h>

void displayInBits(unsigned n, size_t size){
  int i =0;
  //printf("Sachin's DisplayBits() \n");
  //printf("\n\t Size = %d\n\n",size);

  for(i=size*8-1; i>=0; i--){
    ((n>>i) & 1) ? putchar('1'): putchar('0');
    if(!(i%4))
      printf(" ");
  }
  printf("\n");
}

unsigned getBits(unsigned n, int p, int x){

  printf("\nSachin's getBits() \n");
  //return ((n>> (p-x+1)));
  // & (~(~0<<x)));
  //return (~(~0<<x)?~(~0<<x):(~0));
  return ((n>>(p+1-x)) & (~(~0<<x)?~(~0<<x):(~0)));
}

unsigned invert(unsigned x, int p, int n)
{
  printf("\nWeb InvertBits() \n");
  //return  ((~(~0<<n)));
  //return  ((~(~0<<n))<< p+1-n);
  return x ^ ((~(~0<<n))<< p+1-n);
}

unsigned invertBits(unsigned n , int p, int x){

  printf("\nSachin's InvertBits() \n");
  return (n ^ (~(~0<<x)<<(p+1-x)));
  //return (~(n<<(p+1-x)) & orig);

}

int main(){
  unsigned n = 0x12345678;
  int p=0, x=0;
  printf("\n\n");
  displayInBits(n,sizeof(n));

  printf("\n\tEnter Position(p):");
  scanf("%d",&p);

  printf("\n\tEnter Length(x):");
  scanf("%d",&x);

  unsigned n2 = getBits(n, p, x);
  displayInBits(n2, sizeof(n2));

  unsigned n3 = invertBits(n, p, x);
  displayInBits(n3, sizeof(n3));

  unsigned n4 = invert(n, p, x);
  displayInBits(n4, sizeof(n4));



}
