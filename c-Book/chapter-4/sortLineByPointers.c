#include <stdio.h>
#include <string.h>
#define MAXLINES 5000
#define MAXLEN 1000
#define MAXSTORE 10000 /* max space allocated for all lines.  Same as ALLOCSIZE on p.91. */


char *lineptr[MAXLINES];
char lines[MAXLINES][MAXLEN];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int my_getline(char *, int);

void qsort(char *lineptr[], int left, int right);

int readlines2(char *lineptr[], int maxlines)
{
  int len, nlines;


  nlines = 0;
  while ((len = my_getline(lines[nlines], MAXLEN)) > 0)/*lines[nlines] is the address of the n-th lines.*/
    if (nlines >= maxlines)                         
      return -1;           
    else {
      lines[nlines][len - 1] = '\0';  /* delete the newline */
      lineptr[nlines] = lines[nlines]; /* track of the pointer to n-th lines.*/
      nlines++; /* increment n*/
    }
  return nlines;
}

main()
{
  int nlines;
  char linestore[MAXSTORE]; /* array for storing all lines */
  /* myreadlines will pass an extra parameter linestore for storing all the input lines */
  if ((nlines = readlines2(lineptr, MAXLINES)) >= 0)
  {
    qsort(lineptr, 0, nlines-1);
    writelines(lineptr, nlines);
    return 0;
  }
  else
  {
    printf("error: input too big to sort\n");
    return 1;
  }
}



void writelines(char *lineptr[], int nlines)
{
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}

/* K&R2 p97 */

void qsort(char *v[], int left, int right)
{
  int i, last;
  void swap(char *v[], int i, int j);
  if (left >= right)
    return;
  swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}

/* K&R2 p99 */

void swap(char *v[], int i, int j)
{
  char *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* K&R2 p29 */
int my_getline(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    s[i] = c;
  if (c == '\n') {
    s[i++] = c;
  }
  s[i] = '\0';
  return i;
}



