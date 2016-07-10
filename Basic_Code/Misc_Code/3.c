#include<stdio.h>

main()
{
	static int val=7;
	int data;
	if(--val)
	{
		data = main()+val;
		printf("%d",data);
	}

return 0;
}
