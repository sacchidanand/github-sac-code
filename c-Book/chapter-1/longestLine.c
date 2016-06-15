
#include<stdio.h>
#define MAXLINE 10

/* getline: read a line s, return length */
int mygetline(char s[], int lim)
{
      int c, i;

          for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
                    s[i] = c;
              if (c == '\n') {
                        s[i] = c;
                                ++i;
                                    }
                  s[i] = '\0';

                      return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
      int i;

          i = 0;
              while ((to[i] = from[i]) != '\0')
                        ++i;
}


main()
{
  int len; //current line length
  int max, overMax; //maximim length seen so far
  char line[MAXLINE];    //current input line
  char longest[MAXLINE]; //longest line saved here
  char overline[MAXLINE*MAXLINE]; //all characters over MAXLINE saved here

  max = 0;
  overMax = 0;
  while ((len = mygetline(line, MAXLINE)) > 0) {
    if (len > max) {
      max = len;
      copy(longest, line);
    }

    /****  
     *         *   according mygetline
     *                 *   if length of current line greater than MAXLINE mygetline will set 
     *                         *   line[MAXLINE-1] = '\0' and line[MAXLINE-2] != '\n' 
     *                                 ****/
    if (line[MAXLINE-2] != '\n') {
      int c, over;
      char buffer[MAXLINE*MAXLINE];

      over = 0;
      while ((c = getchar()) != '\n') {
        buffer[over] = c;
        ++over;
      }
      buffer[over] = '\0';

      if (over > overMax) {
        overMax = over;
        copy(longest, line);
        copy(overline, buffer);
      }
    } 


  } 

  if (max > 0)
    printf("%s", longest);
  if (overMax > 0)
    printf("%s", overline);

  return 0;
}

