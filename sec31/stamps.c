/*
ID: mickeyj1
TASK: stamps
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_NUM_STAMPS_USED 200
#define MAX_NUM_STAMPS 50
#define MAX_STAMP_VALUE 10000

int
main(int argc, char** argv, char** envp) {
  /* 0 means not possible, otherwise the possible_amounts[i] denotes the
   * minimal number of coins needed to get to the amount.
   */
  int possible_amounts[MAX_NUM_STAMPS_USED * MAX_STAMP_VALUE + 1] = {0};
  int num_stamps_used;
  int num_stamps;
  int stamps[MAX_NUM_STAMPS];
  int length_seq;
  int max_value = 0;
  int bound;
  int i, j;

  FILE* fin = fopen("stamps.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d%d", &num_stamps_used, &num_stamps);
  for (i = 0; i < num_stamps; i++) {
    fscanf(fin, "%d", stamps + i);
    if (stamps[i] > max_value) {
      max_value = stamps[i];
    }
  }
  fclose(fin);

  bound = max_value * num_stamps_used;
  for (i = 0; i < num_stamps; i++) {
    possible_amounts[stamps[i]] = 1;
    for (j = stamps[i] + 1; j <= bound; j++) {
      if (possible_amounts[j - stamps[i]] &&
        possible_amounts[j - stamps[i]] < num_stamps_used && (
          !possible_amounts[j] ||
          possible_amounts[j - stamps[i]] + 1 < possible_amounts[j]
        )
      ) {
        possible_amounts[j] = possible_amounts[j - stamps[i]] + 1;
      }
    }
  }

  length_seq = 0;
  for (i = 1; i <= bound && possible_amounts[i]; i++) {
    length_seq++;
  }

  FILE* fout = fopen("stamps.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", length_seq);
  fclose(fout);

  return EXIT_SUCCESS;
}
