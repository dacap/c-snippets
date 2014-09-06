/* printf - Copyright (C) 2000, 2001 by David A. Capello.
 *
 * - muestra cómo imprimir cada tipo de variable mediante la función "printf()";
 * - it shows how to print each variable type by means of the function "printf()";
 */

#include <stdio.h>
#include <limits.h>
#include <math.h>



int main(void)
{
  char           a = CHAR_MAX;
  short          b = SHRT_MAX;
  int            c = INT_MAX;
  long           d = LONG_MAX;
  unsigned char  e = UCHAR_MAX - 1;
  unsigned short f = USHRT_MAX;
  unsigned int   g = UINT_MAX;
  unsigned long  h = ULONG_MAX;
  float          i = (float)(M_PI);
  double         j = (double)(M_PI);

  printf("char           a = `%c' (%d)\n", a, a);
  printf("short          b = %hd\n", b);
  printf("int            c = %d\n", c);
  printf("long           d = %ld\n", d);
  printf("unsigned char  e = `%c' (%d)\n", e, e);
  printf("unsigned short f = %hu\n", f);
  printf("unsigned int   g = %u\n", g);
  printf("unsigned long  h = %lu\n", h);
  printf("float          i = %f\n", i);
  printf("double         j = %f\n", j);

  return 0;
}



