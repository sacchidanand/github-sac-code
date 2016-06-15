#include <stdio.h>


//#define clrscr() 100
#define clrscr(a) #a

int main()
{
clrscr();
//printf("%d",clrscr());
printf("%s",clrscr("sa"));
return 0;
}

