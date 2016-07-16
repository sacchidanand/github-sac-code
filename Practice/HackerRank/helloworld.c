#include<stdio.h>
#include<stdlib.h>

int main()
{
  char input_string[100];

  printf("\n Please enter the string :\n");

  //Regex used for accepting input string
  scanf("%[^\n]", input_string);

  printf("Hello World.\n");
  printf("%s",input_string);  

  return 0;

}

