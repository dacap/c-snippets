/* strtok - una forma de crear su propia y mejorada strtok()
 * Copyright (C) 2001 por David A. Capello
 */

#include <stdio.h>
#include <string.h>



/* la función es igual que el strtok() normal de libc, solamente
   que esta, al finalizar de procesar la cadena (cuando devuelve
   NULL), deja a la misma como la primera vez que entró, de más
   está decir que también soporta anidamientos */
char *mi_strtok(char *s1, const char *set)
{
/* máxima cantidad de anidamientos */
#define LLAMADAS 256

  /* es un pequeño índice que se utiliza para saber que cadena se
     está utilizando en los arreglos cadenas[] y caracteres[]
     (el nivel de anidamiento en uso) */
  static int c = -1;

  /* guarda los punteros a las cadenas que se están procesando */
  static char *cadenas[LLAMADAS];

  /* guarda el caracter que se tachó con un caracter NULL para luego
     restaurar la cadena una vez utilizado el `token' */
  static char caracteres[LLAMADAS];

  /* si `s1' es una nueva cadena, quiere decir que hay que comenzar
     el proceso para ella */
  if (s1) {
    /* la cadena a procesar por próximas llamas será una totalmente nueva */
    c++;
  }
  /* si el caracter que se tapó en la cadena procesando, era NULL,
     quiere decir que se llegó al final de la tarea */
  else if (!caracteres[c]) {
    /* pasa a la anterior cadena que se estaba procesando */
    c--;

    /* devolver NULL, que significa que terminó todo */
    return (char *)0;
  }
  else {
    /* restaurar el caracter de la cadena */
    *cadenas[c] = caracteres[c];

    /* `s1' es igual a la posición del caracter de adelante del
       recién restaurado */
    s1 = cadenas[c]+1;
  }

  /* buscar por algún caracter de `set' en la cadena `s1' */
  cadenas[c] = strpbrk(s1, set);

  /* sino se encontró ningún caracter... */
  if (!cadenas[c])
    /* asignarle la última posición en la cadena a `cadenas[c]' */
    cadenas[c] = s1+strlen(s1);

  /* guardar el caracter encontrado por strpbrk()... */
  caracteres[c] = *cadenas[c];

  /* ...y pasarlo a NULO para que quede como el fin del `token' */
  *cadenas[c] = 0;

  /* retornar `s1' que contiene la posición inicial del `token' */
  return s1;

#undef LLAMADAS
}



int main(void)
{
  /* la primer cadena */
  char buf1[] = "primer buffer con palabras";

  /* la segunda */
  char buf2[] = "a;b,c";

  /* variables para reservar los `tokens' */
  char *tok1, *tok2;

  /* imprimimos los valores con los que entran a mi_strtok() */
  printf("ENTRADA:\n");
  printf("  buf1 = \"%s\"\n", buf1);
  printf("  buf2 = \"%s\"\n", buf2);

  /* pasar por la primer cadena por todas las palabras separadas por espacio */
  for (tok1=mi_strtok(buf1, " ");
       tok1;
       tok1=mi_strtok(NULL, " ")) {
    printf("tok1 = \"%s\"\n", tok1);

    /* por cada palabra encontrada, se buscará en la 2da cadena palabras
       separadas por `;' o `,' */
    for (tok2=mi_strtok(buf2, ";,");
         tok2;
         tok2=mi_strtok(NULL, ";,")) {
      printf("tok2 = \"%s\"\n", tok2);
    }
  }

  /* mostrar con los valores que salen los buffer al terminar mi_strtok() */
  printf("SALIDA:\n");
  printf("  buf1 = \"%s\"\n", buf1);
  printf("  buf2 = \"%s\"\n", buf2);

  return 0;
}
