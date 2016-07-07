
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

#define SQR(N) (N) * (N)

static int table[100000];

int data;

void* alloc(size_t size)
{
	return malloc(size);	
}

int main()
{
	static int private[SIZE] = {0};
	char *ch= (char*) alloc(SIZE);
	int local = SQR(9+5);
	
	printf("\n.stack   @ %p\n", &local);
	printf(".heap    @ %p\n", ch);
	printf(".bss     @ %p\n", table);
	printf(".data  	 @ %p\n", private);
	printf(".rel.text@ %p\n", printf);
	printf(".text    @ %p\n", main); 

	while(1)
	;	
}

