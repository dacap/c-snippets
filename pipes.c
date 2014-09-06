/* pipes - comunicación de dos procesos mediante tuberías
 * Copyright (C) 2001 por David A. Capello
 */

/* pid_t */
#include <sys/types.h>

/* fork, pipe, close */
#include <unistd.h>

/* FILE *, fdopen, printf, fclose, fgetc, fputc, fflush */
#include <stdio.h>

/* función principal, desde aquí comienza el programa */
int main()
{
  /* descriptores de los ficheros (filedesc[0]=entrada, filedesc[1]=salida) */
  int filedesc[2];

  /* código identificador de cada uno de los procesos */
  pid_t pid;

  /* flujo para controlar los fichero */
  FILE *f;

  /* último caracter leido/escrito */
  int c;

  /* abrir las dos tuberías (la de entrada y salida) */
  if (pipe(filedesc) < 0)
    /* pipe() < 0, error */
    return 1;

  /* crear un subproceso hijo */
  pid = fork();

  /* fork() < 0, error */
  if (pid < 0)
    return 1;

  /* proceso hijo (pid == 0) */
  if (pid == 0) {
    /* cerrar la tubería de salida (total nosotros solamente
       queremos leer de ella, no escribir en ella) */
    close(filedesc[1]);

    /* abrir el descriptor del fichero de entrada en un flujo */
    f = fdopen(filedesc[0], "r");

    /* leer hasta final del fichero */
    while ((c = fgetc(f)) != EOF)
      /* mostrar un mensaje */
      printf("Read: \'%c\'\n", c);

    /* cerrar el flujo */
    fclose(f);
  }
  /* proceso padre (pid > 0) */
  else {
    /* cerrar la tubería de entrada (total nosotros solamente
       queremos escribir en ella, no leer de ella) */
    close(filedesc[0]);

    /* abrir el descriptor del fichero de salida en un flujo */
    f = fdopen(filedesc[1], "w");

    /* leer caracter por caracter de STDIN, hasta EOF (fin-del-fichero) */
    while ((c = fgetc(stdin)) != EOF) {
      /* imprimir mensaje en la pantalla */
      printf("Write: \'%c\'\n", (c & 0xff));

      /* imprimir el caracter leido */
      fputc(c, f);

      /* fluir el contenido escrito en el fichero de salida */
      fflush(f);
    }

    /* cerrar el flujo */
    fclose(f);
  }

  /* todo bien */
  return 0;
}
