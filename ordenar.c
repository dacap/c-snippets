/* ordenar - Copyright (C) 2000, 2001 by David A. Capello.
 *
 * - muestra cómo ordenar un arreglo (array) de números enteros;
 * - it shows how to order an array of integer numbers;
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void ordenar_tabla_de_menor_a_mayor(int *array, int elementos)
{
  int i, j, aux;

  /* recorremos todos los elementos,
     desde el primero hasta el anteúltimo
     (ya que el último quedará siempre en
      la última posición) */
  for (i=0; i<elementos-1; i++) {
    /* comenzamos a buscar desde el próximo elemento
       del actual (i+1), y vamos hasta el final */
    for (j=i+1; j<elementos; j++) {
      /* comparamos, si el primero es mayor,
         debe ir al final, por lo que intercambiaremos
         los valores (esto se conoce como "swap") */
      if (array[i] > array[j]) {
        aux = array[i];      /* guardamos el valor [i] */
        array[i] = array[j]; /* le asignamos [j] a [i] */
        array[j] = aux;      /* le asignamos "aux" a [j] */
      }
    }
  }
}



int main(void)
{
/* cantidad de elementos a ordenar */
#define ELEMENTOS     18

  /* tabla a ordenar */
  int array[ELEMENTOS];
  int i;

  /* semilla del generador de números al azar */
  srand((unsigned)time(NULL));

  /* generar los números e imprimirlos desordenados */
  printf("DESORDENADOS:\t");
  for (i=0; i<ELEMENTOS; i++) {
    array[i] = rand() & 15;
    printf("%d,", array[i]);
  }
  printf("\n");

  /* ordenar la tabla */
  ordenar_tabla_de_menor_a_mayor(array, ELEMENTOS);

  /* imprimir la tabla ordenada */
  printf("ORDENADOS:\t");
  for (i=0; i<ELEMENTOS; i++)
    printf("%d,", array[i]);
  printf("\n");

  return 0;
}



