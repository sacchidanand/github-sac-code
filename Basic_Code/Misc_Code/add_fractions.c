/************************************************************************
 * Author:   M.J. Leslie
 * Purpose:  Add two fractions together.
 * Date:     04-Oct-94
 ************************************************************************/
/******************* Structures *****************************************/

					/* Define a structure to hold the
					 * fraction			*/
struct fract
	{
	int num;			/* Numerator			*/
	int den;                        /* Denominator			*/
	};
/******************* Declare Functions **********************************/

void print_title(void);			/* O/P the title information.	*/

					/* Get the fraction from the
					 * user.			*/
void read_fract(struct fract *);
					/* Add fractions by passing the
					 * whole structure to the function.
					 */
struct fract add_fraction1(struct fract, struct fract);

					/* Add fractions by passing
					 * pointers to the structures.
					 */
void add_fraction2(struct fract *, struct fract *, struct fract *);

					/* Print fractions		*/
void print_fraction(char *, struct fract fraction, char *);

/****************** Main ************************************************/

main ()
   {
					/* Declare the structures that
					 * hold the fractions		*/
   struct fract fract1, fract2, out_fract;

   print_title();			/* airy-fairy title		*/

					/* Get the fraction values
					 * from the user		*/
   read_fract(&fract1);
   read_fract(&fract2);

   puts("\n Passing structure to function gives:");
   print_fraction(" ",fract1, " + ");
   print_fraction("",fract2, " = ");
					/* add the fractions together	*/
   out_fract = add_fraction1(fract1, fract2);
   print_fraction("",out_fract, "\n");

   puts("\n Passing structure pointers to function gives:");
   print_fraction(" ",fract1, " + ");
   print_fraction("",fract2, " = ");
   add_fraction2(&fract1, &fract2, &out_fract);
   print_fraction("",out_fract, "\n");

   return(1);
   }
/************************************************************************/
void print_title(void)
   {
   puts("\n This is a C education program that will add fractions.");
   puts(" It demonstrates the technic of copying structures to ");
   puts(" functions and copying pointers to structures to functions.");
   puts("\n As a by-product the program will ask for two fractions");
   puts(" that are added together and the result put on the screen");
   puts(" ");
   }
/************************************************************************/
void read_fract(struct fract *fract)
   {
   char value[80];

   puts(" ");
   printf(" Please enter the numerator ===> ");
   gets(value);
   fract->num = atoi(value);

   printf(" Please enter the denominator => ");
   gets(value);
   fract->den = atoi(value);
   }
/************************************************************************/
struct fract add_fraction1(struct fract f1, struct fract f2)
   {
   struct fract answer;
					/* get the comman denominator 	*/
   answer.den = f1.den * f2.den;
					/* sort out the numerators	*/
   f1.num = (answer.den / f1.den) * f1.num;
   f2.num = (answer.den / f2.den) * f2.num;
					/* Add up the numerators	*/
   answer.num = f1.num + f2.num;
   return (answer);
   }
/************************************************************************/
void add_fraction2(struct fract *f1, struct fract *f2, struct fract *answer)
   {
					/* Use temps so we do not corrupt
					 * The original values of f1 and
					 * f2				*/
   int temp1, temp2;
					/* get the comman denominator 	*/
   answer->den = f1->den * f2->den;
					/* sort out the numerators	*/
   temp1 = (answer->den / f1->den) * f1->num;
   temp2 = (answer->den / f2->den) * f2->num;
					/* Add up the numerators	*/
   answer->num = temp1 + temp2;
   }
/************************************************************************/
void print_fraction(char * string1, struct fract fraction, char * string2)
   {
					/* Format the fraction with
					 * information strings around it
					 */
   printf("%s%d/%d%s", string1, fraction.num, fraction.den, string2);

   }

