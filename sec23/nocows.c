/*
ID: mickeyj1
TASK: nocows
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_NUM_NODES 199
#define MAX_HEIGHT 99
#define DIVIDER 9901

int
main(int argc, char** argv, char** envp) {
  int nocows[MAX_NUM_NODES + 1][MAX_HEIGHT + 1] = {{0}};
  nocows[1][1] = 1;
  int num_nodes, height;
  int i, j;

  FILE* fin = fopen("nocows.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d %d", &num_nodes, &height);
  fclose(fin);

  int m, n;
  int tmp;
  for (i = 3; i <= num_nodes; i += 2) {
    for (j = 2; j <= height; j++) {
      /*
      this is good but 1 << j can go out of chart.
      if (i < (j << 1) - 1 || i > (1 << j) - 1) {
        continue;
      }
      */
      for (m = 1; m <= i - 2; m += 2) {
        for (n = 1; n <= j - 1; n++) {
          if (i - 1- m < 0) {
            continue;
          }
          /* don't repeat */
          if (m < i - 1 - m && n == j - 1) {
            continue;
          }
          tmp = nocows[m][j - 1] * nocows[i - 1 - m][n];
          if (m != i - 1- m || j - 1 != n) {
            tmp <<= 1;
          }
          nocows[i][j] += tmp % DIVIDER;
        }
      }
      nocows[i][j] %= DIVIDER;
    }
  }

/*
  for (i = 0; i <= num_nodes; i++) {
    printf("%3d ", i);
    for (j = 0; j <= height; j++) {
      printf("%9d ", nocows[i][j]);
    }
    printf("\n");
  }
*/

  FILE* fout = fopen("nocows.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", nocows[num_nodes][height]);
  fclose(fout);

  return EXIT_SUCCESS;
}
