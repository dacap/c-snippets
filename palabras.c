/* palabras - Copyright (C) 2000, 2001 by David A. Capello.
 *
 * - separa cada palabra de una oración;
 * - it separates each word of a sentence;
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#undef NULL
#define NULL 0



/* en esta función obtenemos desde una cadena, todo una nueva tabla
   con cada una de las palabras que existe en la cadena;
   recuerde el `const char *', esto indica que la cadena no será
   modificada dentro de la función, y por lo tanto, la tabla
   contendrá todos nuevos bloques de memoria (que por sierto,
   luego deberán ser liberados) */
char **obtener_palabras(const char *cadena)
{
  char **tabla;
  int palabras;
  int longitud;
  int i, j, k;

  /* primero debemos obtener la cantidad de palabras que existe en
     la cadena de caracteres... */
  palabras = 0;

  /* ...para ésto, solamente debemos buscar por toda la cadena... */
  for (i=1; cadena[i]; i++) {
     /* ...la cantidad de espacios no consecutivos
        que existen en la misma... */
    if ((cadena[i] == ' ') && (cadena[i] != cadena[i-1]))
      palabras++;
  }

  /* ...y luego sumarle un valor más (si no es que al final
     de la cadena existe un espacio (ej: "hola ")) */
  if (cadena[i-1] != ' ')
    palabras++;

  /* mostramos un mensaje para mostrar cuantas palabras se encontraron */
  printf("Palabradas encontradas: %d\n", palabras);

  /* una vez que tenemos la cantidad de palabras, hay que comenzar el
    trabajo difícil, que es ir separando toda la cadena */

  /* 1ro: comenzamos por reservar al doble puntero un espacio en memoria
     para una cantidad de N cadenas (en este caso indicado por `palabras') */
  tabla = (char **)malloc(sizeof(char *) * (palabras + 1));
  /* ...recuerda que hay que utilizar (palabra + 1), ya que la último
     cadena será igual a NULL, la cual indicará el final */

  /* DEMONIOS!... ¿tenemos que comprar más RAM? :-) */
  if (!tabla)
    return NULL;

  /* 2do paso: buscar todas las palabras */
  for (i=k=0; i<palabras; i++) {
    /* buscar el primer caracter que no sea un espacio */
    for (j=k; (cadena[j] == ' '); j++);

    /* luego, desde ahí, buscar un caracter que sea un espacio (o el final
       de la cadena) */
    for (k=j; ((cadena[k] != ' ') && (cadena[k] != 0)); k++);

    /* calcular la longitud que hay entre el principio y el final de
       la palabra encontrada */
    longitud = k - j;

    /* reservar memoria suficiente como para guardar la palabra */
    tabla[i] = (char *)malloc(sizeof(char) * (longitud + 1));
    /* ...recuerda el (longitud + 1), ya que necesitaremos un caracter
       más para poder indicar el final de la cadena (el caracter 0) */

    if (!tabla[i])
      return NULL;

    /* copiamos la palabra */
    memcpy(tabla[i], &cadena[j], longitud);

    /* caracter final de la cadena */
    tabla[i][longitud] = 0;
  }

  /* ahora `i', queda con el valor que será el último elemento de la tabla */
  tabla[i] = NULL;

  /* y bueno, por fin, ya estamos en condiciones de retornar nuestra
     tabla con todas las palabras por separado */
  return tabla;
}



/* la función principal */
int main(void)
{
  /* creamos nuestra oración de prueba */
  char *mi_oracion = "   Hoy    es    un    hermoso dia... en  el  infierno!!!   :-)   ";
  /* esta variable contendrá cada una de las palabras en "mi_oracion" */
  char **mi_argv;
  /* un simple e ignificante índice */
  int i;

  /* imprimimos la oración a procesar */
  printf("\n\nOración: \"%s\"\n", mi_oracion);

  /* obtenemos todas las palabras de la oración */
  mi_argv = obtener_palabras(mi_oracion);

  /* ¿error? */
  if (!mi_argv) {
    printf("Error! No hay memoria suficiente...\n");
    return 1;
  }

  /* vamos escribiendo todas las palabras que obtuvimos de `mi_cadena'
     mientras que esa palabra sea diferente a NULL (el final de la tabla) */
  for (i=0; mi_argv[i]; i++) {
    printf("Palabra #%02d: `%s'\n", i, mi_argv[i]);

    /* borramos de la memoria la palabra (ya que no la utilizaremos
       más en el programa) */
    free(mi_argv[i]);
  }

  /* y por último borramos el puntero completamente */
  free(mi_argv);

  /* no hay errores */
  return 0;
}



