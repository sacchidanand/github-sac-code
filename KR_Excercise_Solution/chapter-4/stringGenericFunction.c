#include <stdio.h>

#define STR_BUF    10000
#define STR_MATCH  7 /* Used as the base number of characters to match with. */

char *my_strncpy (char *, char *, int);
char *my_strncat (char *, char *, int);
int   my_strncmp (char *, char *, int);
int   my_strlen  (char *);

int main(int argc, char *argv[])
{
  int result;
  char str_s[STR_BUF] =  "All along the watchtower.";
  char buf_1[STR_BUF];
  char buf_2[STR_BUF] = "Bob Dylan: ";
  char buf_3[STR_BUF] = "All along the Watchposition.";

  printf ("----------------------------------------------------------\n");
  printf ("  Base String: %s\n", str_s);
  printf ("----------------------------------------------------------\n");

  my_strncpy (buf_1, str_s, STR_MATCH);
  printf ("buf_1 (my_strncpy, 7 chars): %s\n", buf_1);

  my_strncat (buf_2, str_s, STR_MATCH);
  printf ("buf_2 (my_strncat, 5 chars): %s\n", buf_2);

  result = my_strncmp(buf_3, str_s, STR_MATCH);

  printf ("buf_3 (my_strncmp, 6 chars): %s\n", buf_3);

  if ( result == 0 ) {
    printf ("my_strncmp result: Both strings match up to %d char(s).\n",
        STR_MATCH );
  } else if ( result == -1 ) {
    printf ("my_strncmp result: Strings do not match, buf_3 string ");
    printf ("has a lesser value.\n");
  } else if ( result == 1 ) {
    printf ("my_strncmp result: Strings do not match, ");
    printf ("base string has a greater value than buf_3.\n");
  }

  return 0;
}

/*
 * Copy at most n characters of string ct to s; return s.
 */
char *my_strncpy (char *s, char *ct, int n)
{
  int count = 1;
  while ((*s++ = *ct++)) {
    if (count++ == n) {
      break;
    }

  }
  return s;
}

/*
 *  * Concatenate at most n characters of string ct to string s, terminate s with
 *   * '\0'; return s.
 *    */
char *my_strncat (char *s, char *ct, int n)
{
  int i = 0;
  int len = my_strlen(s);
  for (i = 0; n > 0; i++, n--) {
    *(s + len + i) = *ct++;
  }
  *(s + len + i) = '\0';
  return s;
}

/*
 *  * Compare at most n characters of string cs to string ct; return < 0 if
 *   * cs < ct, 0 if cs == ct, or > 0 if cs > ct.
 *    */
int my_strncmp (char *cs, char *ct, int n)
{
  int i;

  for (i = 0; i < n; i++) {
    if (*(cs+i) < *(ct+i)) {
      return -1;
    } else if (*(cs+i) > *(ct+i)) {
      return 1;
    }
  }

  return 0;
}

int my_strlen (char *s)
{
  int count = 0;
  while (*s++ != '\0') {
    count++;
  }
  return count;
}

