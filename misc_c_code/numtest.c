/**************************************************************************
 *
 * Purpose: find the smallest and largest numbers from a sequence of numbers.
 * to do:   Change it so it will take any number of numbers from the keyboard.
 * Author:  M. J. Leslie
 * Date:    04-Apr-94
 *
 **************************************************************************/

#include <stdio.h>

#define MAX_NUM 4

float bignum   (float, float);
float littlenum(float, float);

main()
{
float numbers[MAX_NUM]= {0};
float biggest=0, littlest=999;
int count;

for (count = 0; count < MAX_NUM; count++)
   {
		printf(" %f \n",numbers[count]);
	}
puts("Please enter 4 numbers");
scanf("%f %f %f %f", &numbers[0], &numbers[1], &numbers[2], &numbers[3]);                         

for (count = 0; count < MAX_NUM; count++)
   {
	   biggest  = bignum(numbers[count], biggest);
	   littlest = littlenum(numbers[count], littlest);
   }
printf("Biggest number is %f\n",  biggest);
printf("Littlest number is %f\n", littlest);
}

float bignum( float num1, float num2)
{
if ( num1 > num2)
   return num1;
else
   return num2;
}

float littlenum( float num1, float num2)
{
if ( num1 < num2)
   return num1;
else
   return num2;
}
