#include <stdio.h>
#define swap(t, x, y) \
  x = x + y;\
  y = x - y; \
  x = x - y; \


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
  printf("integers after swap: %g and %g\n", dx, dy);

  px = "hello";
  py = "world";
  printf("pointers before swap: %s and %s\n", px, py);
//  swap(char *, px, py);
  printf("integers after swap: %s and %s\n", px, py);

  return 0;
}


