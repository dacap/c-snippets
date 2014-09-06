/* calendar - a portable way to show the calendar of the current month
 * Copyright (C) 2001 by David A. Capello
 */

#include <stdio.h>
#include <time.h>

int main(void)
{
  char *months_table[12] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
  };
  int c, day, month;
  struct tm *tmd;
  time_t tod;

  /* get the amount of seconds since January 1, 1970 */
  tod = time(NULL);

  /* transform the seconds to the `tm' structure */
  tmd = localtime(&tod);

  /* day of the month (1-31) */
  day = tmd->tm_mday;

  /* month of the year (0-11) */
  month = tmd->tm_mon;

  /* print a header */
  printf("-- %s del %d --\n", months_table[month],
                              tmd->tm_year + 1900);

  printf("Do Lu Ma Mi Ju Vi Sa\n");

  /* retrogress the amount of seconds from the current day
     to the first day of the month */
  tod -= 24L*60L*60L*(tmd->tm_mday-1);
  tmd = localtime(&tod);

  /* print some extra blanks to begin to print the first day of the month */
  for (c=0; c<tmd->tm_wday; c++)
    printf("   ");

  /* print day-by-day until arrive the next month */
  while (month == tmd->tm_mon) {
    printf("%2d%s", tmd->tm_mday, (tmd->tm_mday == day)? "<": " ");

    /* if this is Saturday (the day in the last column)
       we must make a line-return so the next Sunday will
       be written below */
    if (tmd->tm_wday == 6)
      printf("\n");

    /* go ahead to the next day (24hs * 60min * 60sec) */
    tod += 24L*60L*60L;
    tmd = localtime(&tod);
  }

  /* an extra line-return */
  printf("\n");
  return 0;
}
