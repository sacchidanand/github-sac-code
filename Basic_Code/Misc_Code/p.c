
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char c[10000],*k;
	int count[10000];
	int len=0;
	
	printf("\n Enter String :");
	scanf("%s",k);
	printf("\n String = %s \n\n",k);
	
	len=strlen(k);
	printf("\n String = %s  len = %d \n\n",k,len);
	
}
