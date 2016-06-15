#include <stdio.h>

#define swap(t,x,y)                                     \
  do {                                                    \
    (unsigned char *)_0=(unsigned char *)(&(x));        \
    (unsigned char *)_1=(unsigned char *)(&(y));        \
    unsigned long _2 = (unsigned long)                  \
    ((unsigned char *)(&(x)+1)                       \
     - (unsigned char *)(&(x)));                     \
    while (_2--) {                                      \
      *_0 ^= *_1;                                     \
      *_1 ^= *_0;                                     \
      *_0 ^= *_1;                                     \
      _0++;                                           \
      _1++;                                           \
    }                                                   \
  } while (0)

int main(void) {
  int ix, iy;
  double dx, dy;
  char *px, *py;

  ix = 42;
  iy = 69;
  printf("integers before swap: %d and %d\n", ix, iy);
  swap(int, ix, iy);
  printf("integers after swap: %d and %d\n", ix, iy);

  dx = 123.0;
  dy = 321.0;
  printf("doubles before swap: %g and %g\n", dx, dy);
  swap(double, dx, dy);
  printf("doubles after swap: %g and %g\n", dx, dy);

  px = "hello";
  py = "world";
  printf("pointers before swap: %s and %s\n", px, py);
  swap(char *, px, py);
  printf("pointers after swap: %s and %s\n", px, py);

  return 0;
}

