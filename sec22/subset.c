/*
ID: mickeyj1
TASK: subset
LANG: C
*/
#include <stdio.h>
#include <assert.h>

#define MAX_N 39
#define MAX_SUM (((1 + MAX_N) * MAX_N) >> 1)

long long
solve(int n) {
  long long sum = ((1 + n) * n) >> 1;
  if ((sum & 0x1) == 1) {
    return 0;
  }
  long long half_sum = sum >> 1;

  long long dp_table[MAX_N + 1][(MAX_SUM >> 1) + 1];
  int i, j;
  for (i = 0; i <= n; i++) {
    dp_table[i][0] = 1;
  }
  for (i = 1; i <= half_sum; i++) {
    dp_table[0][i] = 0;
  }
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= half_sum; j++) {
      dp_table[i][j] = dp_table[i - 1][j] +
        ((j - i < 0)? 0: dp_table[i - 1][j - i]);
    }
  }

  return dp_table[n][half_sum] >> 1;
}

int
main(int argc, char** argv, char** envp) {
  int n;
  FILE* fin = fopen("subset.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d", &n);
  fclose(fin);

  FILE* fout = fopen("subset.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%lld\n", solve(n));
  fclose(fout);

  return 0;
}
