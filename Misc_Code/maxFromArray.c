#include <stdio.h>

int main(int argc, char* argv[])
{
		int totalNumber=0,max,i=0;
		totalNumber=atoi(argv[1]);
		int a[totalNumber];
		
		/*	To read input from user	*/
		for(i=0;i<totalNumber;i++){
			printf("\n Enter number a[%d] = ",i);
			scanf("%d",&a[i]);
		}
		
		max=a[0];
	
		/*To find maximum number from an array	*/
		for(i=1;i<totalNumber;i++){
			if(max<a[i])
				max=a[i];
		}
		printf("\n Maximum number = %d\n\n ",max);
return 0;	
}
