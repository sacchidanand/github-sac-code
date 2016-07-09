/************************************************************************
 *
 * Purpose: Display the name of the program.
 * To do:   Stip any directory information away so we are left with 
 *	    with the file name only.
 * Author:  M.J.Leslie
 * Date:    09-Jan-95
 *
 ************************************************************************/

main(int argc, char *argv[])
{
  char *prog=argv[0];

				/* prog_name points to the same location 
				 * as argv[0]
				 */
  printf("Program is called %s\n", prog);
}
