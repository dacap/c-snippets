/* strtok - a way to create your own and improved strtok()
 * Copyright (C) 2001 by David A. Capello
 */

#include <stdio.h>
#include <string.h>



/* this function is the same of libc's strtok(), just which this,
   when finish the string-processing (when it returns NULL), leave
   the string intact like the first call, this routine support
   nestles */
char *my_strtok(char *s1, const char *set)
{
/* maximum nestle's level */
#define CALLS 256

  /* a little index to see which string is used in the strings[]
     and characters[] arrays (the current nestle level) */
  static int c = -1;

  /* keeps the pointers to the strings in process */
  static char *strings[CALLS];

  /* keeps the character that was replaced with NULL, for then
     to restore the string when the `token' is used */
  static char characters[CALLS];

  /* if `s1' is a new string, this means which we need to begin the process
     with this */
  if (s1) {
    /* the string to process in the next calls will be a completelly new one */
    c++;
  }
  /* if the replaced character in the string in process was NULL,
     this means which we are in the end of the work */
  else if (!characters[c]) {
    /* go the previous string in process */
    c--;

    /* return NULL, which means that all end */
    return (char *)0;
  }
  else {
    /* restore the replaced character in the string */
    *strings[c] = characters[c];

    /* `s1' is equal to the next position of the character of the recent
       restored one */
    s1 = strings[c]+1;
  }

  /* search for some character of `set' in the `s1' string */
  strings[c] = strpbrk(s1, set);

  /* if we don't found a character... */
  if (!strings[c])
    /* assign the last position in the string to `strings[c]' */
    strings[c] = s1+strlen(s1);

  /* keep the founded character by strpbrk()... */
  characters[c] = *strings[c];

  /* ...and pass it to NULL for to remain like the end of the `token' */
  *strings[c] = 0;

  /* returns `s1' which contains the initial position of the `token' */
  return s1;

#undef CALLS
}



int main(void)
{
  /* the first string */
  char buf1[] = "first buffer with words";

  /* the second one */
  char buf2[] = "a;b,c";

  /* variables to store the `tokens' */
  char *tok1, *tok2;

  /* we print the input values to the my_strtok() routine */
  printf("INPUT:\n");
  printf("  buf1 = \"%s\"\n", buf1);
  printf("  buf2 = \"%s\"\n", buf2);

  /* pass for the first string for each word separated by spaces */
  for (tok1=my_strtok(buf1, " ");
       tok1;
       tok1=my_strtok(NULL, " ")) {
    printf("tok1 = \"%s\"\n", tok1);

    /* for each founded word, we will search in the 2nd string words
       separated by `;' or `,' */
    for (tok2=my_strtok(buf2, ";,");
         tok2;
         tok2=my_strtok(NULL, ";,")) {
      printf("tok2 = \"%s\"\n", tok2);
    }
  }

  /* we show the buffers after the my_strtok() routine */
  printf("OUTPUT:\n");
  printf("  buf1 = \"%s\"\n", buf1);
  printf("  buf2 = \"%s\"\n", buf2);

  return 0;
}



