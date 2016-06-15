#include<stdio.h>
//123.45e-6
double atof_sachin(char *);
int main()
{
  char s1[] = "87.549e2", s2[] = "-982.47e-3", s3[] = "-54e", s4[] = "-.64e4", s5[] = "+.87e+ 6";
  printf("s1 = %10s <-> %15lf\n", s1, atof_sachin(s1));
  printf("s2 = %10s <-> %15lf\n", s2, atof_sachin(s2));
  printf("s3 = %10s <-> %15lf\n", s3, atof_sachin(s3));
  printf("s4 = %10s <-> %15lf\n", s4, atof_sachin(s4));
  printf("s5 = %10s <-> %15lf\n", s5, atof_sachin(s5));
  return 0;
}

/*
int main(){
  char s[] = "123.45e-6";
  double answer = atof_sachin(s);
  printf("\n\n Input = %10s\n\n Answer = %lf",s,answer);
}
*/
double atof_sachin(char *s){
  double result = 0.0, exponent=0.0;
  int decimalFlag=0, k=0, i=0, sign=1, c;

  if(s[0]=='-')
    sign = -1;

  while((c=s[i++]) != '\0')
  {
    if(c == 'e' || c=='E')
    { 
      exponent = atof_sachin(&s[i]);
      break;
    } 
     
    if(c=='.')
      decimalFlag=1;
    else if(c>='0' && c<='9')
    {
      if(decimalFlag==1)
        ++k;
      result = (c-'0') + (result*10);
    }
  }

  exponent = exponent - k;
  
  if(exponent<0){
    while(exponent++)
      result = result / 10.0;
  }
  else if(exponent>0){
    while(exponent--)
      result = result * 10.0;
  }

  return result*sign;
}

