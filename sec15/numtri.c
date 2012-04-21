/*
ID: mickeyj1
LANG: C
TASK: numtri
*/
#include <stdio.h>
#include <assert.h>

#define MAX_LEN 1000

int
main(int argc, char** argv) {
  int num_rows;
  int max = 0;
  int row0[MAX_LEN];
  int row1[MAX_LEN];
  int* prev_row = row0;
  int* curr_row = row1;
  int* tmp;
  int i, j;

  FILE* fin = fopen("numtri.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d", &num_rows);
  for (i = 1; i <= num_rows; i++) {
    for (j = 0; j < i; j++) {
      fscanf(fin, "%d", curr_row + j);
    }
    if (i > 1) {
      curr_row[0] += prev_row[0];
      curr_row[i - 1] += prev_row[i - 2];
      for (j = 1; j < i - 1; j++) {
        curr_row[j] +=
          (prev_row[j - 1] > prev_row[j])? prev_row[j - 1]: prev_row[j];
      }
    }
    tmp = prev_row;
    prev_row = curr_row;
    curr_row = tmp;
  }
  fclose(fin);
  for (i = 0; i < num_rows; i++) {
    if (prev_row[i] > max) {
      max = prev_row[i];
    }
  }

  FILE* fout = fopen("numtri.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", max);
  return 0;
}
