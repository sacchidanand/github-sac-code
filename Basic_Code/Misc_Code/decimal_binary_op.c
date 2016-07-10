/************************************************************************
 *
 * Purpose: Display a byte in binary format.
 * 
 * Author:  M.J. Leslie.
 *
 * Date:    19-Mar-95
 *
 * Improvements: 
 *	1) Return the result to the calling function.
 *	2) Make it work on integers (4 bytes long).
 *
 ************************************************************************/

void binary_op(char byte);		/* Print a byte in binary.	*/

/************************************************************************/

main()
   {
		char byte=8;	
		scanf("%d",&byte);
		binary_op(byte);			/* Print a byte in binary.	*/
   }

/************************************************************************/

void binary_op(char byte)
   {
   int count=8;				/* Number of bits in a byte.	*/

   while(count--)
      {
					/* AND the high order bit (the
					 * left one) If the bit is set,
					 * print a ONE.			*/
      printf("%d", ( byte & 128 ) ? 1 : 0 );

					/* Move all the bits LEFT.	*/
      byte <<= 1;
      } 

   printf("\n");
   }

/************************************************************************
 *
 *	Program results.
 *	----------------
 *
 *	00110111
 *
 ************************************************************************/
