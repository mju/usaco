/*
ID: mickeyj1
TASK: ratios
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define UPPER_BOUND 100
#define NUM_MIXTURES 3

int
cmp_tuples(const char* lhs, const char* rhs) {
  int sum_lhs = lhs[0] + lhs[1] + lhs[2];
  int sum_rhs = rhs[0] + rhs[1] + rhs[2];
  if (sum_lhs != sum_rhs) {
    return sum_lhs - sum_rhs;
  }
  if (lhs[0] != rhs[0]) {
    return lhs[0] - rhs[0];
  }
  if (lhs[1] != rhs[1]) {
    return lhs[1] - rhs[1];
  }
  return lhs[2] - rhs[2];
}

/* return -1 if not; otherwise the multiplier. */
int
is_multiple(char* ratios, char* goal, char mixtures[][NUM_MIXTURES]) {
  int multiplier =
    (int)mixtures[0][0] * (int)ratios[0] +
    (int)mixtures[1][0] * (int)ratios[1] +
    (int)mixtures[2][0] * (int)ratios[2];
  if (multiplier % goal[0] != 0) {
    return -1;
  }
  multiplier /= goal[0];
  if (
    (int)mixtures[0][1] * (int)ratios[0] + (int)mixtures[1][1] * (int)ratios[1] +
    (int)mixtures[2][1] * (int)ratios[2] != (int)goal[1] * multiplier
  ) {
    return -1;
  }
  if (
    (int)mixtures[0][2] * (int)ratios[0] + (int)mixtures[1][2] * (int)ratios[1] +
    (int)mixtures[2][2] * (int)ratios[2] != (int)goal[2] * multiplier
  ) {
    return -1;
  }
  return multiplier;
}

int
main(int argc, char** argv, char** envp) {
  char goal[NUM_MIXTURES];
  char mixtures[NUM_MIXTURES][NUM_MIXTURES];
  char multipliers[
    (UPPER_BOUND + 1) * (UPPER_BOUND + 1) * (UPPER_BOUND + 1)
  ][NUM_MIXTURES];
  int i, j, k;
  int num_multipliers = 0;
  int multiplier;

  FILE* fin = fopen("ratios.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d%d%d", &i, &j, &k);
  goal[0] = (char)i;
  goal[1] = (char)j;
  goal[2] = (char)k;
  fscanf(fin, "%d%d%d", &i, &j, &k);
  mixtures[0][0] = (char)i;
  mixtures[0][1] = (char)j;
  mixtures[0][2] = (char)k;
  fscanf(fin, "%d%d%d", &i, &j, &k);
  mixtures[1][0] = (char)i;
  mixtures[1][1] = (char)j;
  mixtures[1][2] = (char)k;
  fscanf(fin, "%d%d%d", &i, &j, &k);
  mixtures[2][0] = (char)i;
  mixtures[2][1] = (char)j;
  mixtures[2][2] = (char)k;
  fclose(fin);

  for (i = 0; i <= UPPER_BOUND; i++) {
    for (j = 0; j <= UPPER_BOUND; j++) {
      for (k = 0; k <= UPPER_BOUND; k++) {
        multipliers[num_multipliers][0] = i;
        multipliers[num_multipliers][1] = j;
        multipliers[num_multipliers][2] = k;
        num_multipliers++;
      }
    }
  }
  assert(num_multipliers == 
    (UPPER_BOUND + 1) * (UPPER_BOUND + 1) * (UPPER_BOUND + 1)
  );
  qsort(
    multipliers,
    num_multipliers,
    NUM_MIXTURES,
    (int(*)(const void*, const void*))cmp_tuples
  );

  FILE* fout = fopen("ratios.out", "w");
  assert(fout != NULL);

  /* skip 0, 0, 0. */
  for (i = 1; i < num_multipliers; i++) {
    multiplier = is_multiple(multipliers[i], goal, mixtures);
    if (multiplier != -1) {
      fprintf(fout, "%d %d %d %d\n",
        multipliers[i][0], multipliers[i][1], multipliers[i][2], multiplier
      );
      fclose(fout);
      return EXIT_SUCCESS;
    }
  }

  fprintf(fout, "NONE\n");
  fclose(fout);
    
  return EXIT_SUCCESS;
}
