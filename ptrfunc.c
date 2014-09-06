/* ptrfunc - Copyright (C) 2000, 2001 by David A. Capello.
 *
 * - muestra cómo hacer punteros a funciones;
 * - it shows how to make pointers to functions;
 */

#include <stdio.h>


/* definimos el tipo de variable para punteros a funciones */
typedef int (*mi_func)(int, int);


/* cuatro funciones que son del mismo formato que `mi_func' */
static int suma(int x, int y)           { return x+y; }
static int resta(int x, int y)          { return x-y; }
static int multiplicacion(int x, int y) { return x*y; }
static int division(int x, int y)       { return x/y; }


/* una tabla con cuatro funciones */
static mi_func funciones[] = { suma, resta, multiplicacion, division };



int main()
{
  /* tres variables:
       x = valor 1;
       y = valor 2;
       c = operación; */
  int x, y, c;

  printf("Ingrese tres números separados por espacios:\n"
         "1er  = primer número (x)\n"
         "2do  = segundo número (y)\n"
         "3ero = operación:\n"
         "\t0 = x+y\n"
         "\t1 = x-y\n"
         "\t2 = x*y\n"
         "\t3 = x/y\n");

  scanf("%d %d %d", &x, &y, &c);

  /* si `c' no está entre 0 y 3, la operación no existe */
  if ((c < 0) || (c > 3)) {
    printf("Error!... operación inválidad...\n");
    return 1;
  }

  /* división por cero... esto suena feo... */
  if ((c == 3) && (!y)) {
    printf("Error!... división por cero...\n");
    return 1;
  }

  /* llamamos la función */
  c = (*funciones[c])(x, y);

  /* imprimimos el resultado */
  printf("Resultado: %d\n\n", c);
  return 0;
}


