#include <stdio.h>
#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("error: stack is full, can't execute ungetch()\n");
	else
		buf[bufp++] = c;
}

