/************************************************************************
 *
 * Purpose: Second crack at a lottery number selector.
 * Author:  M.J. Leslie.
 * Date:   03-Dec-94
 * Description: Any 6 random numbers from 1 to 49 are displayed. 
 *              Duplicates are removed and the results sorted.
 *
 ************************************************************************/

/********** Preprocessor  ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBERS 6

/********** Functions ***************************************************/

void display_nums(int *, int);
int comp_nums(const int *, const int *);

/************************************************************************/
main()
   {
   int num[NUMBERS];			/* array holding the selected
					 * numbers			*/
   int count;				/* General  counter		*/
		

   printf("\n\nLOTTERY CRACKER V1.1\n");
   printf("--------------------\n\n");
   printf("\tPossible winning ticket number is ");

					/* New starting point
					 * for the random number generator.
					 */

   srand((unsigned int)time((time_t *)NULL));

					/* Collect Six numbers.	
					 * Filter out duplicats as we go.
					 */
   {
   int dup, count2;
   for (count=0; count < NUMBERS; count++) 
      {
      num[count]=(rand()%49)+1;		/* Get a number.		*/
      dup=0; 				/* Set the duplicate flag to 
					 * NO DUPLICATES		*/
					/* Test latest number with the ones
				 	 * already held.		*/
      for (count2=0 ; count2 < count; count2++)
         {
					/* If match found - set flag.	*/
         if (num[count] == num[count2]) dup++ ;
         }
					/* If flag set - reset the array
					 * index so we overwrite the current
					 * number.			*/
      if (dup > 0 ) count--;
      }
   }
					/* Sort the numbers		*/
   qsort(
	num, 				/* Pointer to elements		*/
	NUMBERS, 			/* Number of elements		*/
	sizeof(int),  			/* size of one element.		*/
	(void *)comp_nums		/* Pointer to comparison function */
	);

   display_nums(num, NUMBERS); 		/* Display the results		*/
   }

/************************************************************************
 *
 * comp_nums: Compare two numbers.
 *
 ************************************************************************/

int comp_nums(const int *num1, const int *num2)
   {
   return (*num1 - *num2);
   }

/************************************************************************
 *
 * display_nums: Display the numbers
 *
 ************************************************************************/

void display_nums(int *array, int count)
   {
					/* Print all the elements of 
					 * the array.               	*/
   while ( count-- ) 
      {
      printf("%d ",*array);
      array++;
      }
   puts("");
   puts("");
   }
