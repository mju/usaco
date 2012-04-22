/*
ID: mickeyj1
LANG: C
TASK: checker
*/
#include <stdio.h>
#include <assert.h>

#define MAX_DIM 13
#define NUM_SOLS_TO_OUTPUT 3

void
backtrack(
  int row,
  int dim,
  char* row2col,
  char* col,
  char* pos_diagonal,
  char* neg_diagonal,
  int* num_sols,
  FILE* fout
) {
  if (row == dim) {
    if (*num_sols < NUM_SOLS_TO_OUTPUT) {
      fprintf(fout, "%d", row2col[0] + 1);
      int i;
      for (i = 1; i < dim; i++) {
        fprintf(fout, " %d", row2col[i] + 1);
      }
      fprintf(fout, "\n");
    }
    *num_sols = *num_sols + 1;
    return;
  }
  int i;/* for column. */
  int pos_dia_idx;
  int neg_dia_idx;
  for (i = 0; i < dim; i++) {
    pos_dia_idx = row + i;
    neg_dia_idx = row - i + (dim - 1);
    if (
      col[i] == 0 &&
      pos_diagonal[pos_dia_idx] == 0 &&
      neg_diagonal[neg_dia_idx] == 0
    ) {
      col[i] = 1;
      pos_diagonal[pos_dia_idx] = 1;
      neg_diagonal[neg_dia_idx] = 1;
      row2col[row] = i;
      backtrack(
        row + 1, dim, row2col, col, pos_diagonal, neg_diagonal, num_sols, fout
      );
      col[i] = 0;
      pos_diagonal[pos_dia_idx] = 0;
      neg_diagonal[neg_dia_idx] = 0;
    }
  }
}

int
main(int argc, char** argv) {
  int dim;
  FILE* fin = fopen("checker.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d", &dim);
  fclose(fin);

  /* elements denote the columns. */
  char row2col[MAX_DIM];
  char col[MAX_DIM] = {0};
  char pos_diagonal[(MAX_DIM << 1) - 1] = {0};
  char neg_diagonal[(MAX_DIM << 1) - 1] = {0};

  FILE* fout = fopen("checker.out", "w");
  assert(fout != NULL);
  int num_sols = 0;
  backtrack(0, dim, row2col, col, pos_diagonal, neg_diagonal, &num_sols, fout);
  fprintf(fout, "%d\n", num_sols);
  fclose(fout);

  return 0;
}
