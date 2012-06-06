/*
ID: mickeyj1
TASK: inflate
LANG: C
*/
/* WARNING: not the best solution given that dp_tbl[total_minutes]
 * always contains the maximum of points which can be achieved.
 */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_NUM 10000

int
main(int argc, char** argv, char** envp) {
  int dp_tbl[MAX_NUM + 1] = {0};
  int max_points = 0;
  int total_minutes;
  int num_categories;
  int points;
  int minutes;
  int i;

  FILE* fin = fopen("inflate.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d%d", &total_minutes, &num_categories);
  for (; num_categories; num_categories--) {
    fscanf(fin, "%d%d", &points, &minutes);
    for (i = minutes; i <= total_minutes; i++) {
      if (dp_tbl[i - minutes] + points > dp_tbl[i]) {
        dp_tbl[i] = dp_tbl[i - minutes] + points;
        if (dp_tbl[i] > max_points) {
          max_points = dp_tbl[i];
        }
      }
    }
  }
  fclose(fin);

  FILE* fout = fopen("inflate.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", max_points);
  fclose(fout);

  return EXIT_SUCCESS;
}
