/*
ID: mickeyj1
LANG: C
TASK: barn1
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_NUM_STALLS 200

int
cmp_int(const int* lhs, const int* rhs) {
  return *lhs - *rhs;
}

int
main(int argc, char** argv) {
  int num_boards;
  int num_stalls;
  int num_cows;
  int cows[MAX_NUM_STALLS];
  int i;

  FILE* fin = fopen("barn1.in", "r");
  assert(fin != NULL);

  fscanf(fin, "%d %d %d", &num_boards, &num_stalls, &num_cows);
  for (i = 0; i < num_cows; i++) {
    fscanf(fin, "%d", cows + i);
  }

  fclose(fin);

  /* the problem statement guarantees that there is at least one cow. */
  qsort(
    cows, num_cows, sizeof(cows[0]), (int(*)(const void*, const void*))cmp_int
  );

  int num_stalls_blocked = cows[num_cows - 1] - cows[0] + 1;

  for (i = 1; i < num_cows; i++) {
    cows[i - 1] = cows[i] - cows[i - 1] - 1;
  }

  qsort(
    cows,
    num_cows - 1,
    sizeof(cows[0]),
    (int(*)(const void*, const void*))cmp_int
  );

  for (
    i = 0, num_cows -= 2; i < num_boards - 1 && num_cows >= 0; i++, num_cows--
  ) {
    num_stalls_blocked -= cows[num_cows];
  }

  FILE* fout = fopen("barn1.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", num_stalls_blocked);
  fclose(fout);

  return 0;
}
