#include <stdio.h>
#include <string.h>

int ischar(char c)
{
  if ((c >='0' && c <='9') ||
      (c >='a' && c<='z')   ||
      (c >='A' && c<='Z'))
  {
    return 1;
  }
  return 0;
}

void copyseq(char **s2, char begin, char end)
{
  while (begin <= end){
    *((*s2)++) = begin++;
  }
}

void expand(char* s1, char* s2)
{
  char* print_end = 0;
  
  while(*s1)
  {
    if (*s1 == '-')
    {
      if (ischar(*(s1-1)) && ischar(*(s1+1)))
      {
    
        if (print_end && print_end == (s1-1)) {
          copyseq(&s2, *(s1-1)+1, *(s1+1));
          print_end = s1+1;
        }
        else{
          copyseq(&s2, *(s1-1), *(s1+1));
          print_end = s1 + 1;
        }
      }
    }
    
    if (print_end != s1 && print_end != s1+1){
      *s2++ = *s1;
      print_end = s1;
    }

    ++s1;
  }
  *s2 = *s1;
}

int main()
{
  char s1[100];
  char s2[100];

  strcpy(s1, "a-d-e-f-5-8-0-9a-b-d-f-g-");
  //strcpy(s1, "a-d-e-f0-9a-b-d-f-g-");
  printf("\nInput : %s\n\n", s1);
  
  expand(s1, s2);
  
  printf("\nExpanded Output : %s\n\n", s2);
}


