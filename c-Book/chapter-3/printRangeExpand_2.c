/* *   EX3_3.C
       2nd Alternative solution to Exercise 3-3
 *       */
#include <stdio.h>
#include <ctype.h>

#define INPUT 100
#define OUTPUT 500
#define STR_SIZE 30
#define DASH '-'

int getinp(char []);
void explow(int, int);
char store[STR_SIZE];

int main ()
{
  char s[INPUT], t[OUTPUT];
  int i,j,prv,nxt;

  for(i = 0; i < INPUT; i++) /* To flush input string */
    s[i] = 0;
  
  for(i = 0; i < OUTPUT; i++) /* To flush output string */
    t[i] = 0;
  
  j = prv = nxt = 0;

  if (getinp(s)) 
  {
    for(i=0; s[i] == DASH;i++)                                        /* Fill input with leading '-', if there is any */
      t[i] = s[i];
    j = i;
  
    while (s[i] != '\0') 
    {
      
      if (s[i] != DASH)
        t[j++] = s[i++];
      else if (s[i] == DASH)  {
        prv = s[i-1], nxt = s[i+1];
        
        if ((islower(prv) && islower(nxt)) || (isupper(prv) && isupper(nxt)) || (isdigit(prv) && isdigit(nxt))) 
        {
          explow(prv,nxt);
          prv = nxt = 0;
          t[j] = '\0';
          strcat(t,store);
          j = strlen(t);
          i++;
        }
        else
          t[j++] = s[i++];
      }
    }
    printf("%s\n",t);
  }
  else
    printf("INPUT MISSING !!!!\n");
  return 0;
}

/*-------------------------------------------------------------------------------------------*/

int getinp(char ip[]) /* function is ready */
{
  int i,c;
  i = 0;

  while (c = getchar()) 
  {
    if (isalnum(c) || c == DASH) /* Get all alpha numeric and '-' into input string */
      ip[i] = c;
    else
      switch (c) 
      { /* ignore all irrelevant blank spaces */
        case '\t': case '\v': case '\b': case '\r':
        case '\f': case '\\': case '\'': case '\"':
                                         break;
        case '\n': case EOF: /* Signal to mark end of input */
                                         ip[i] = '\0';
                                         break;
        default:
                                         break;
      }
   
    if (ip[i++] == '\0')
      break;
  }
  return i-1;  /* for zero input, it will return zero */
}

/*--------------------------------------------------------------------------------------------*/
void explow(int a, int z) {
  int i,j;
  extern char store[];

  for(i = 0; i < STR_SIZE; i++) /*flush the array */
    store[i] = 0;
  i = 0;

  if (a < z){
    for (i = 0; (a+=1) < z; i++)
      store[i] = a;
  }
  else if (a > z) {
    for (i = 0; (a-=1)>z;i++){
      store[i] = a;
    }
  }
  return ;
}


