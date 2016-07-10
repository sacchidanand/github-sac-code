#include <stdio.h>

int main()
{
	int i=1, num=0, j=1;
	printf ("\n\n Enter the number: ");
	scanf ("%d", &num );

	for (i=1; i<=num; i++)
		j=j*i;    

	printf("\n\n The factorial of %d is %d\n",num,j);
	return 0;
}

