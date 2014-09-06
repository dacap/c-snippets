/* regex - cómo utilizar expresiones regulares en un programa
 * Copyright (C) 2001 por David A. Capello
 */

#include <stdio.h>
#include <regex.h>

int main(int argc, char *argv[])
{
  char buf[256];
  regex_t regex;

  /* error si no se especifica por lo menos un argumento */
  if (argc < 2) {
    printf("Usage:\n\t%s regex\n", argv[0]);
    return 1;
  }

  /* compilar la expresión regular */
  if (regcomp(&regex, argv[1], REG_EXTENDED | REG_NOSUB) == 0) {
    /* leer desde la entrada estandard línea por línea */
    while (fgets(buf, sizeof(buf), stdin)) {
      /* imprimir `Bingo!' cuando la expresión regular se acomode a esa línea */
      if (regexec(&regex, buf, 0, NULL, 0) == 0)
        fprintf(stdout, "Bingo!\n");
    }
    /* liberar la expresión regular compilada */
    regfree(&regex);
  }

  /* no hay error */
  return 0;
}
