#include<stdio.h>

#define swap(a,b) do{typeof(a) _tmp = a; a=b; b=_tmp;}while(0)


int main()
{
int a = 10, b = 20; 

printf("Before \n a=%d b=%d\n",a,b);
swap(a,b);
printf("After \n a=%d b=%d\n",a,b);

printf("\n typeof a=%s b=%s\n",typeof(a),typeof(b));

return 0;
}
