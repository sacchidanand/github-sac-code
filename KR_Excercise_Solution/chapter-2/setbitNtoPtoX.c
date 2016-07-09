#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
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

unsigned getBits(unsigned n, int p, int x){
  //return ((n>> (p-x+1)));
  //return  ((~(~0<<x)));
  //return (~(~0<<x)?~(~0<<x):(~0));
  return ((n>>(p+1-x)) & (~(~0<<x)?~(~0<<x):(~0)));
}

uint32_t changeEndianNess_sachin(uint32_t value){
  uint32_t temp = ~(~0U);
  printf("\nSachin version ChangeEndianNess");
  return ((((value>>24 |temp)| value<<24) | (((value>>16) & ~(~0<<8))<<8)) | (((value>>8) & ~(~0<<8))<<16));
  //return  (((value>>16) & ~(~0<<8) ));
  //return (~((uint32_t)~0>>8));
  //return (((value<<16) & ~(~0>>8)   ));

}

uint32_t changeEndianNess(uint32_t value){
//unsigned changeEndianNess(unsigned value){

  unsigned result = ~(~0);
  printf("\nWeb version ChangeEndianNess");
  result |= (0x000000FF & value) << 24; 
  result |= (0xFF000000 & value) >> 24; 
  result |= (0x0000FF00 & value) << 8; 
  result |= (0x00FF0000 & value) >> 8 ; 
  return result;
}


unsigned setBitsYinX(unsigned x, int p, int n, unsigned y){
 
  unsigned msk = ~(~0<<n);
  return ((~(msk<<p-n+1)));
  //return ((x & ~(msk<<p-n+1)));
  //return (((y & msk) << p-n+1));
  //return ((x & ~(msk<<p-n+1)) | ((y & msk) << p+1-n));
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned msk = ~(~0 << n);
    return (x & ~(msk<< p+1-n)) | ((y & msk)<< p+1-n);
}





int main(){
  unsigned n = 0x12345678;
  unsigned y = 0xFFFFFFFF; 
  unsigned number2 = 0x1234;
  int number3 = 4660, number4= 305419896;
  int p=0, x=0;

  //printf("\nEnter number:");
  //scanf("%d",&number4);

  //displayInBits(n,sizeof(n));
  
  //displayInBits(number2,sizeof(number2));  
  //displayInBits(number3,sizeof(number3));
  //
  /*
  displayInBits(number4,sizeof(number4));
  printf("\nAfter change in Endian:\n");
  number4 = changeEndianNess_sachin(number4);
  displayInBits(number4,sizeof(number4));
  number4 = changeEndianNess(number4);
  displayInBits(number4,sizeof(number4));
  */

  //number4 = changeEndianNess(number4);
  //n = changeEndianNess(n);
  //displayInBits(n,sizeof(n));

  //int pos=0;
  //printf("\nEnter number:");
  //scanf("%d",&pos);
  //uint32_t g = ~(~0<<pos);
  //displayInBits(g,sizeof(g));

/*  
  printf("\n\nEnter Number:");
  scanf("%d",&p);

  printf("\n\nEnter x:");
  scanf("%d",&x);

  unsigned n2 = getBits(n, p, x);
  printf("\n\n getBits = ");
  displayInBits(n2, sizeof(n2));
  */

  printf("\n\nEnter Number:");
  scanf("%d",&p);

  printf("\n\nEnter x:");
  scanf("%d",&x);

  displayInBits(n, sizeof(n));
  displayInBits(y, sizeof(y));

  //unsigned ydash = setbits(n, p, x, y);
  unsigned ydash = setBitsYinX(n, p, x, y);
  displayInBits(ydash, sizeof(ydash));
}
