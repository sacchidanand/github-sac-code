/* Exercise 4-2. Extend atof to handle scientific notation of the form
 *   123.45e-6 
 *  where a floating-point number may be followed by e or E and an optionally signed exponent.
 * 
 * I wrote up a recursive solution. Turns out Adam beat me to it. But I've avoided using the pow() function
 * to keep this a category 0 solution. */

#include <stdio.h>
double atof(char *s)
{
  double result = 0.0, exponent = 0.0;
  int i = 0, c, sign = 1, flag = 0, k = 0;

  if(s[0] == '-')
    sign = -1;

  while( (c = s[i++]) != '\0')
  {
    
    //123.45e-6 
    if(c == 'e' || c =='E'){
      exponent = atof(&s[i]);
      break;
    }//endif-1
    
    if(c == '.')
      flag = 1;
    else if(c >= '0' && c <= '9' )
    {
      if(flag == 1)
        ++k;
      result = (c - '0') + (result * 10);
    }//endif-2
  
  }//while-end

  exponent = exponent - k;
  
  if(exponent < 0)
  {
    while(exponent++)
      result /= 10.0;
  }
  else if(exponent > 0)
  {
    while(exponent--)
      result *= 10.0;
  }

  return sign * result;
}

int main()
{
  char s1[] = "87.549e2", s2[] = "-982.47e-3", s3[] = "-54e", s4[] = "-.64e4", s5[] = "+.87e+ 6";
  printf("s1 = %10s <-> %15lf\n", s1, atof(s1));
  printf("s2 = %10s <-> %15lf\n", s2, atof(s2));
  printf("s3 = %10s <-> %15lf\n", s3, atof(s3));
  printf("s4 = %10s <-> %15lf\n", s4, atof(s4));
  printf("s5 = %10s <-> %15lf\n", s5, atof(s5));
  return 0;
}


