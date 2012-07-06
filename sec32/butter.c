/*
ID: mickeyj1
TASK: butter
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_NUM_PASTURES 800
#define UNDEFINED -1

int
main(int argc, char** argv, char** envp) {
  int num_cows;
  int num_pastures;
  int num_paths;
  int map[MAX_NUM_PASTURES][MAX_NUM_PASTURES];
  short pos_cows[MAX_NUM_PASTURES] = {0};
  int min_dist = UNDEFINED;
  int i, j, k;
  int dist;

  FILE* fin = fopen("butter.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d%d%d", &num_cows, &num_pastures, &num_paths);
  for (i = 0; i < num_cows; i++) {
    fscanf(fin, "%d", &j);
    pos_cows[j - 1]++;
  }
  for (i = 0; i < num_pastures; i++) {
    for (j = 0; j < num_pastures; j++) {
      if (i == j) {
        map[i][j] = 0;
      } else {
        map[i][j] = UNDEFINED;
      }
    }
  }
  for (i = 0; i < num_paths; i++) {
    fscanf(fin, "%d%d%d", &j, &k, &dist);
    map[j - 1][k - 1] = dist;
    map[k - 1][j - 1] = dist;
  }
  fclose(fin);

  /* run floyd-warshall. */
  for (i = 0; i < num_pastures; i++) {
    for (j = 0; j < num_pastures - 1; j++) {
      if (map[j][i] == UNDEFINED) {
        continue;
      }
      for (k = j + 1; k < num_pastures; k++) {
        if (map[i][k] == UNDEFINED) {
          continue;
        }
        if (map[j][i] + map[i][k] < map[j][k] || map[j][k] == UNDEFINED) {
          map[j][k] = map[k][j] = map[j][i] + map[i][k];
        }
      }
    }
  }

  for (i = 0; i < num_pastures; i++) {
    dist = 0;
    for (j = 0; j < num_pastures; j++) {
      /* when there are no cows in the jth pasture, skip the iteration. */
      if (pos_cows[j] == 0) {
        continue;
      }
      /* some coews cannot reach pasture i. */
      if (map[j][i] == UNDEFINED) {
        dist = UNDEFINED;
        break;
      }
      dist += pos_cows[j] * map[j][i];
    }
    if (dist != UNDEFINED && (min_dist == UNDEFINED || dist < min_dist)) {
      min_dist = dist;
    }
  }

  FILE* fout = fopen("butter.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", min_dist);
  fclose(fout);

  return EXIT_SUCCESS;
}
