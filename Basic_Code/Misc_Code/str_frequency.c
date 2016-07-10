#include <stdio.h>
//#include <string.h>

main()
{
	char str1[] = "Hello Big Boy";
	char *t1;


//for ( t1 = strtok(str1," "); t1 != NULL; t1 = strtok(NULL, " ") )
	t1 = strtok(str1," ");
	printf("\n %s\n",t1);
	
	return 0;	
}
