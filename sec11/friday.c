/*
ID: mickeyj1
LANG: C++
TASK: friday
*/
#include <stdio.h>

#define MONTHS 12
#define DAYS 7
#define YEAR_START 1900
/* the 13th of January in 1900 is a Saturday. */
#define FIRST_THIRTEEN 0

int
is_leap_year(int year) {
  return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
}

int
main(int argc, char** argv) {
  FILE *fin = fopen("friday.in", "r");
  FILE *fout = fopen("friday.out", "w");
  int n;
  fscanf(fin, "%d", &n);

  int thirteenths[DAYS];/* SAT, SUN, MON, TUE, WED, THU, FRI */
  thirteenths[0] = 0;
  thirteenths[1] = 0;
  thirteenths[2] = 0;
  thirteenths[3] = 0;
  thirteenths[4] = 0;
  thirteenths[5] = 0;
  thirteenths[6] = 0;

  int days_month[MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  int day = FIRST_THIRTEEN;
  int i, j;
  for (i = YEAR_START; i < n + YEAR_START; i++) {
    if (is_leap_year(i)) {
      days_month[1] = 29;
    } else {
      days_month[1] = 28;
    }
    for (j = 0; j < MONTHS; j++) {
      thirteenths[day]++;
      day += days_month[j];
      day %= DAYS;
    }
  }

  fprintf(
    fout, "%d %d %d %d %d %d %d\n",
    thirteenths[0],
    thirteenths[1],
    thirteenths[2],
    thirteenths[3],
    thirteenths[4],
    thirteenths[5],
    thirteenths[6]
  );

  fclose(fin);
  fclose(fout);
  return 0;
}
