#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>

/*  unsigned n = 0x12345678;
 *  displayInBits(n,sizeof(n));
 */
void displayInBits(unsigned n, size_t size)
{
    int i =0;

    for(i=size*8-1; i>=0; i--)
    {
      ((n>>i) & 1) ? putchar('1'): putchar('0');
      if(!(i%4))  
        printf(" ");    
    }                     
    printf("\n");           
} 

void changeEndian(uint32_t input, uint32_t *output)
{
  *output = (((0xff000000 & input)>>24) | 
     ((0x00ff0000 & input)>>8) |
     ((0x0000ff00 & input)<<8)  |
     ((0x000000ff & input)<<24));
}

int main(int argc, char*argv[])
{
  struct in_addr litaddr;
  struct in_addr bigaddr;
  bigaddr.s_addr = 0;
  char dest_addr[50];

  inet_aton(argv[1],&litaddr);
  
  printf("\n Little-Endian in Hex = %x", litaddr.s_addr);
  printf("\n Little-Endian in Binary = ");
  displayInBits(litaddr.s_addr,sizeof(litaddr.s_addr));
  
  //Change Endianness
  changeEndian(litaddr.s_addr, &bigaddr.s_addr);

  printf("\n Big-Endian in Hex = %x", bigaddr.s_addr);
  printf("\n Big-Endian in Binary = ");
  displayInBits(bigaddr.s_addr,sizeof(bigaddr.s_addr));

  inet_pton(AF_INET, &*(struct in_addr*)bigaddr.s_addr, &dest_addr);
  printf("\nIn dotted-decimal form %s", dest_addr);

  printf("\n");
  return 0;
}
/*
void bin(unsigned n)
{
  unsigned i;
  for (i = 1 << 31; i > 0; i = i / 2)
    (n & i)? printf("1"): printf("0");
}
*/
