/*
ID: mickeyj1
TASK: concom
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_BOUND 100
#define DEF_OWNING 50

int
main(int argc, char** argv, char** envp) {
  char percentages[MAX_BOUND + 1][MAX_BOUND + 1][MAX_BOUND + 1] = {{{0}}};
  char orig_percentages[MAX_BOUND + 1][MAX_BOUND + 1];
  int owner, ownee, percentage;
  int num_lines;
  char tmp;
  int i, j, k, l;
  int is_changed;

  FILE* fin = fopen("concom.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d", &num_lines);
  for (i = 0; i < num_lines; i++) {
    fscanf(fin, "%d%d%d", &owner, &ownee, &percentage);
    orig_percentages[owner][ownee] = percentages[owner][ownee][0] = (char)percentage;
    percentages[owner][ownee][owner] = 1;
  }
  fclose(fin);

  is_changed = 1;
  while (is_changed) {
    is_changed = 0;
    for (i = 1; i <= MAX_BOUND; i++) {
      for (j = 1; j <= MAX_BOUND; j++) {
        if (percentages[i][j][0] <= DEF_OWNING) {
          continue;
        }
        for (k = 1; k <= MAX_BOUND; k++) {
          for (l = 1; l <= MAX_BOUND; l++) {
            percentages[i][k][l] |= percentages[j][k][l];
          }
        }
      }
      for (j = 1; j <= MAX_BOUND; j++) {
        tmp = 0;
        for (k = 1; k <= MAX_BOUND; k++) {
          if (percentages[i][j][k]) {
            tmp += orig_percentages[k][j];
          }
          if (tmp > percentages[i][j][0]) {
            is_changed = 1;
            percentages[i][j][0] = tmp;
          }
        }
      }
    }
  }

  FILE* fout = fopen("concom.out", "w");
  assert(fout != NULL);
  for (i = 1; i <= MAX_BOUND; i++) {
    for (j = 1; j <= MAX_BOUND; j++) {
      if (i == j) {
        continue;
      }
      if (percentages[i][j][0] > DEF_OWNING) {
        fprintf(fout, "%d %d\n", i, j);
      }
    }
  }
  fclose(fout);

  return EXIT_SUCCESS;
}
