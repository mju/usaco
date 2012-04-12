/*
ID: mickeyj1
LANG: C
TASK: ariprog
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define M 250
#define MIN_LEN 3

int
main(int argc, char** argv) {
  FILE* fin = fopen("ariprog.in", "r");
  assert(fin != NULL);
  int len_prog;
  int m;
  fscanf(fin, "%d %d", &len_prog, &m);
  fclose(fin);

  char mark_bi_squares[((M * M) << 1) + 1] = {0};
  int i, j;
  for (i = 0; i <= m; i++) {
    for (j = i; j <= m; j++) {
      mark_bi_squares[i * i + j * j] = 1;
    }
  }

  int max_bi_square = (M * M) << 1;
  int bi_squares[((M + 1) * ((M + 1) + 1)) >> 1];
  int num_bi_squares = 0;
  for (i = 0; i <= max_bi_square; i++) {
    if (mark_bi_squares[i] == 1) {
      bi_squares[num_bi_squares++] = i;
    }
  }

  FILE* fout = fopen("ariprog.out", "w");
  assert(fout != NULL);

  int max_b = ((m * m) << 1) / (len_prog - 1);
  int k;
  int b;
  int is_valid;
  int num_seq = 0;
  for (i = 1; i <= max_b; i++) {
    for (
      j = 0;
      j < num_bi_squares &&
        bi_squares[j] + (len_prog - 1) * i <= bi_squares[num_bi_squares - 1];
      j++
    ) {
      for (k = 0, b = 0, is_valid = 1; is_valid && k < len_prog; k++, b += i) {
        is_valid = is_valid && mark_bi_squares[bi_squares[j] + b];
      }
      if (is_valid) {
        num_seq++;
        fprintf(fout, "%d %d\n", bi_squares[j], i);
      }
    }
  }
  if (num_seq == 0) {
    fprintf(fout, "NONE\n");
  }

  fclose(fout);

  return 0;
}
