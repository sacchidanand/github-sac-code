/* PROGRAM STARTS HERE...*/
#include <stdio.h>

struct test{
enum{RED, GREEN, BLUE}color;
enum day = { jan = 1 ,feb=4, april, may};
};

void amIColored(struct test * t)
{
	if (t->color==RED)
		printf("\n RED");
	else
		printf("\n I DO NOT KNOW MY COLOR");
}

int main()
{
	struct test t;
	t.color= RED;
	amIColored(&t);
	
return 0;
}
/* PROGRAM ENDS HERE */
