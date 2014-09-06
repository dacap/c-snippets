/* dividator - split words incoming from stdin
 * Copyright (C) 2002 by David A. Capello
 */

#include <stdio.h>
#include <string.h>

/* this routine "eats" tokens from `buf' and returns its */
char *eat_tok(char *buf)
{
  char *tok, *beg, *end;
  int chr;

  /* remove all blank-spaces in the beginning of the buffer */
  for (; (*buf) && (*buf == ' '); buf++);

  /* the buffer has some character for the token? */
  if (*buf) {
    /* the beginning of the token */
    beg = buf;
    /* find the end of the token */
    if (*beg == '\"') {
      /* the token is between quotes */
      for (end=beg+1; (*end) && (*end != '\"'); end++);
      /* include the quote in the token */
      end++;
    }
    else {
      /* the token is separated for blank-spaces */
      for (end=beg; (*end) && (*end != ' '); end++);
    }
    /* duplicate the token */
    chr = *end;
    *end = 0;
    tok = strdup(beg);
    *end = chr;
    /* "eat" the token (removing it from the string) */
    memmove(buf, end, strlen(buf)-(beg-buf+1));
    /* and return the new allocated token */
    return tok;
  }
  /* we finish with this buffer */
  else
    return NULL;
}

int main()
{
  char buf[256];
  char *tok;

  /* read a line from the standard input (the keyboard or a file) */
  while (fgets(buf, sizeof(buf), stdin)) {
    /* remove the last `\n' character from the line */
    if (buf[strlen(buf)-1] == '\n')
      buf[strlen(buf)-1] = 0;
    /* get tokens from the readed line `buf' */
    for (tok=eat_tok(buf); tok;
         tok=eat_tok(buf)) {
      /* print the token */
      printf("%s\n", tok);
      /* free the token */
      free(tok);
    }
  }

  return 0;
}
