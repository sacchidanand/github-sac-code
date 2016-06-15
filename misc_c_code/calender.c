/*
 * Purpose: To generate a calender.
 * Author:  M J Leslie
 * Date:    19-Mar-94
 */

#include <stdio.h>
#define TRUE  		1
#define FALSE 		0

#define DAYS_IN_A_WEEK 	7
#define MAX_COLS       	6
#define BASE_YEAR	1990		/* Year from which all 
					   calculations are done. 	*/

					/* Function declatations	*/
int calender_month(const int month, const int year);
int start_day(const int month, const int year);
int leap(int);

					/* Global variables.		*/
int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};

main(int argc, char  *argv[])
{
  int i;				/* General purpose var		*/
  int year;				/* year to start display	*/
  int num_of_months;			/* Number of months		*/
  int start_month;			/* Start month			*/
  int month;				/* Current month		*/
  char *prog=argv[0];			/* Program name			*/

					/* Check we have the
					   program name and 3 parms	*/
  if ( argc != 4)
    {
      puts("\tProgram syntax:");
      printf("\t\t%s start_month start_year num_of_months",prog );
      exit(1);
    }
					/* Dont bother checking if the
					   parms are integers!!		*/

					/* Put command line parms into
					   meaningfull variable names	*/
  start_month   = atoi(argv[1]);
  year          = atoi(argv[2]);
  num_of_months = atoi(argv[3]);

					/* AND OFF WE GO...		*/
  month = start_month;
  for (i=start_month; i < start_month + num_of_months ; i++)
  {
    calender_month(month, year);	/* O/P one month.		*/
    if ( month++ >= 12)			/* Q. End of year?		*/
    {					/* Yes.				*/
      month = 1;
      year++;
    }
  }
}

/************************************************************************/
/*                    Calender_month                                    */
/*		Display one calender month.				*/
/************************************************************************/

calender_month(const int month, const int year)
{
  int i,j,count;			/* General Purpose variables.	*/

					/* dont forget - arrays start 
					   at zero			*/
  char *days[]=
  {
    " ",
    "Mon",
    "Tue",
    "Wed",
    "Thr",
    "Fri",
    "Sat",
    "Sun"
  };

  char *months[]=
  {
    " ",
    "January",
    "Febuary",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
  };
		

  int month_map[8][MAX_COLS+1]={0};	/* init array with zeros	*/

  j=start_day(month, year);		/* Get the day the month starts */
					/* Build the calender values 	*/
  i=1;count=0;
  while ( days_in_month[month] > count)
  {
    month_map[j++][i]=++count;		/* Build the table.		*/
					/* Start a new week.		*/
    if ( j > DAYS_IN_A_WEEK)
    {
      j=1;
      i++;
    }
  }
					/* O/P Title bar.		*/
  printf("\n\t\t%s %d\n\n",months[month], year);
					/* O/P the calender	 	*/
  for (j=1; j<=DAYS_IN_A_WEEK; j++)
  {
    printf("\t%s ",days[j]);		/* Day names			*/

    for (i=1; i<=MAX_COLS; i++)
    {
      if ( month_map[j][i] == 0 ) 	/* dates			*/
         {printf ("   ");}
      else
         {printf ("%2d ", month_map[j][i]);}
    }

    puts ("");				/* puts supplies a Newline	*/
  }
}

/************************************************************************/
/*                    Start_day 	                                */
/*		Work out which day the month starts on.			*/
/************************************************************************/

int start_day(const int month, const int year)
{
  int day=1;				/* 1/1/1990 was a Monday.       */
  int i,j;				/* GP work variable.		*/

					/* Count days in the year.	*/
  i = BASE_YEAR;

  while ( i < year )
  {
    leap(i);				/* Check for leap years		*/
    for (j=1; j<=12; j++) day = day + days_in_month[j];
    i++;
  }

					/* Count upto the month required */
  i=1;
  leap(year);				/* Check for leap years		*/
  while ( i < month )
  {
    day = day + days_in_month[i++];
  }
					/* Get modulo and return it as
					   the start day for this month	*/
  if ( (day = day%7) == 0 ) day = 7;	/* correct 0 to 7		*/
  return ( day );
}

/************************************************************************/
/*                    leap	 	                                */
/*		Find leap years.                         		*/
/*			Returns 0 - Not a leap year.          		*/
/*			        1 - leap year.          		*/
/************************************************************************/

int leap(int year)
{

        /*
	A leap year follows the following rules:
		if divisable by 4 and not 100 its a leap year.
		if divisable by 400 it is a leap year.
	*/

  if ( (year%4 == FALSE && year%100 != FALSE) || year%400 == FALSE )
  {
    days_in_month[2] = 29;
    return(1);				/* leap year 		*/
  }
  else
  {
    days_in_month[2] = 28;
    return(0);				/* NOT a leap year	*/
  }
}
