#include<stdio.h>
int main()
{
	int x[2]={10,1};
	int *p=x[0];
	int *q=x[1];
	printf("\n The address of x is %d\n",(int)(&p)-(int)(&q));
	return 0;
}
