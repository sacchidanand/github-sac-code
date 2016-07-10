/*************************************************************************
 *
 * Purpose: Numerical exercise with integer arrays. Starting with 0, 1 add 
 * 	    them up then take the result and add it to the last number and 
 * 	    repeat.
 * 
 * 	    For example:
 * 
 * 		0 + 1 = 1
 * 		1 + 1 = 2
 * 		1 + 2 = 3 
 * 
 * Author:  M. J. Leslie
 * Date:    04-Apr-94
 *
 ************************************************************************/

#include <stdio.h>

#define ITTERATIONS 20
				/* NO COMMENTS! can you figure it out? */
main()
{
int num[3]={0,1};
int count1, count2;

printf("%d %d ", num[0], num[1]);
//printf("\n\nnum[2]= %d \n\n", num[2]);

for (count1=0; count1 < ITTERATIONS-2; count1++)
   {
   num[2] = num[0] + num[1];
   printf("%d ",num[2]);
   for (count2 =0; count2 < 2; count2++) num[count2] = num[count2+1];
   }
puts("");
}
