/* calendar - una forma portable para mostrar el calendario del mes actual
 * Copyright (C) 2001 by David A. Capello
 */

#include <stdio.h>
#include <time.h>

int main(void)
{
  char *tabla_de_meses[12] = {
    "Enero",
    "Febrero",
    "Marzo",
    "Abril",
    "Mayo",
    "Junio",
    "Julio",
    "Agosto",
    "Septiembre",
    "Octubre",
    "Noviembre",
    "Diciembre"
  };
  int c, dia, mes;
  struct tm *tmd;
  time_t tod;

  /* obtener la cantidad de segundos que pasaron desde
     el primero de Enero de 1970 */
  tod = time(NULL);

  /* transformar la cantidad de segundos en una estructura `tm' */
  tmd = localtime(&tod);

  /* día del mes (1-31) */
  dia = tmd->tm_mday;

  /* mes del año (0-11) */
  mes = tmd->tm_mon;

  /* imprimir un encabezado */
  printf("-- %s del %d --\n", tabla_de_meses[mes],
                              tmd->tm_year + 1900);

  printf("Do Lu Ma Mi Ju Vi Sa\n");

  /* retrocer la cantidad de segundos que abarca desde el día
     actual hasta el primer día del mes */
  tod -= 24L*60L*60L*(tmd->tm_mday-1);
  tmd = localtime(&tod);

  /* imprimir espacios extras para comenzar a imprimir el
     primer día del mes */
  for (c=0; c<tmd->tm_wday; c++)
    printf("   ");

  /* imprimir los días uno por uno hasta llegar al próximo mes */
  while (mes == tmd->tm_mon) {
    printf("%2d%s", tmd->tm_mday, (tmd->tm_mday == dia)? "<": " ");

    /* si este día es Sábado (el que está en la última columna),
       debemos hacer un retorno de línea para que el Domingo
       próximo se escriba debajo */
    if (tmd->tm_wday == 6)
      printf("\n");

    /* avanzar al próximo día (24hs * 60min * 60seg) */
    tod += 24L*60L*60L;
    tmd = localtime(&tod);
  }

  /* un retorno de línea extra por las dudas */
  printf("\n");
  return 0;
}
