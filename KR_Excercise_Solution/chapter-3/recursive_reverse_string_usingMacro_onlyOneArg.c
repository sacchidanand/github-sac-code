#include <stdio.h>
#include <string.h>

#define reverse(S) doreverse(S, 0, strlen(S) - 1)

/**
 *  * doreverse: reverses string s in place
 *   * Yes, supplying indexes to "reverse" function is ugly.
 *    * But the fact can be hidden with the macro .
 *     */
void doreverse(char s[], int first, int last) {
  char tmp = s[first];
  if (first >= last)
    return;
  s[first] = s[last];
  s[last] = tmp;
  doreverse(s, first + 1, last - 1);
}

int main(int argc, char* argv[]) {
#define NUM_TESTS 4
  char s1[] = "";
  char s2[] = "1";
  char s3[] = "12";
  char s4[] = "Goodbye Cruel World";
  char* s[NUM_TESTS] = {s1, s2, s3, s4};
  int i = 0;
  for (i = 0; i < NUM_TESTS; i++) {
    printf("Original:\t\"%s\"\n", s[i]); reverse(s[i]);
    printf("Reversed:\t\"%s\"\n", s[i]); reverse(s[i]);
    printf("Reversed Twice:\t\"%s\"\n", s[i]);
  }
  return 0;
}

