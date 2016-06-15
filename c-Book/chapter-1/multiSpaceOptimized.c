#include <stdio.h>

main(){
  char c;

  while((c = getchar()) != EOF){
    putchar(c);
    if (c == 0x20){
      while ((c=getchar()) == 0x20);
      putchar(c);
    }
  }
}

