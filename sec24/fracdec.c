/*
ID: mickeyj1
TASK: fracdec
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define SIZE_TABLE 1000000/*10000 * 10*/
#define LEN_LINE 76

struct record {
  int idx;
  char quotient;
  char num_leading_zeros;
};

int
main(int argc, char** argv, char** envp) {
  /* visited[a] is marked if some a/b was being evaluating, where b will
   * never change, and a/b can be visited for that only once.  If a/b is
   * evaluated twice, there is a circle.
   */
  char visited[SIZE_TABLE] = {0};
  struct record metadata[SIZE_TABLE];
  int num_metadata = 0;

  int numerator, denominator;
  int quotient;
  int integer;
  int num_trailing_zeros = 0;

  int num_chars;
  char line[LEN_LINE + 1];
  line[LEN_LINE] = '\0';
  int i, j;

  FILE* fin = fopen("fracdec.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d%d", &numerator, &denominator);
  fclose(fin);

  integer = numerator / denominator;
  numerator -= integer * denominator;

  while (!visited[numerator] && numerator) {
    visited[numerator] = 1;
    metadata[num_metadata].idx = numerator;
    metadata[num_metadata].num_leading_zeros = -1;
    while (numerator < denominator) {
      numerator *= 10;
      metadata[num_metadata].num_leading_zeros++;
      if (numerator < denominator && visited[numerator]) {
        num_trailing_zeros = metadata[num_metadata].num_leading_zeros;
        break;
      }
    }
    if (num_trailing_zeros > 0) {
      break;
    }
    quotient = numerator / denominator;
    metadata[num_metadata].quotient = (char)quotient;
    numerator -= quotient * denominator;
    num_metadata++;
  }

  /* numerator contains the start of the cycle, or zero if there is no cycle */
  FILE* fout = fopen("fracdec.out", "w");
  assert(fout != NULL);

  num_chars = sprintf(line, "%d.", integer);
  assert(num_chars > 0);
  if (numerator == 0) {
    if (num_metadata == 0) {
      line[num_chars++] = '0';
      line[num_chars] = '\0';
      fprintf(fout, "%s\n", line);
    } else {
      for (i = 0; i < num_metadata; i++) {
        for (j = 0; j < metadata[i].num_leading_zeros; j++) {
          if (num_chars == LEN_LINE) {
            fprintf(fout, "%s\n", line);
            num_chars = 0;
          }
          line[num_chars++] = '0';
        }
        if (num_chars == LEN_LINE) {
          fprintf(fout, "%s\n", line);
          num_chars = 0;
        }
        line[num_chars++] = metadata[i].quotient + '0';
      }
      if (num_chars > 0) {
        line[num_chars] = '\0';
        fprintf(fout, "%s\n", line);
      }
    }
  } else {
    for (i = 0; i < num_metadata; i++) {
      if (metadata[i].idx == numerator) {
        if (num_chars == LEN_LINE) {
          fprintf(fout, "%s\n", line);
          num_chars = 0;
        }
        line[num_chars++] = '(';
      }
      for (j = 0; j < metadata[i].num_leading_zeros; j++) {
        if (num_chars == LEN_LINE) {
          fprintf(fout, "%s\n", line);
          num_chars = 0;
        }
        line[num_chars++] = '0';
      }
      if (num_chars == LEN_LINE) {
        fprintf(fout, "%s\n", line);
        num_chars = 0;
      }
      line[num_chars++] = metadata[i].quotient + '0';
    }
    if (num_chars == LEN_LINE) {
      fprintf(fout, "%s\n", line);
      num_chars = 0;
    }
    for (i = 0; i < num_trailing_zeros; i++) {
      line[num_chars++] = '0';
      if (num_chars == LEN_LINE) {
        fprintf(fout, "%s\n", line);
        num_chars = 0;
      }
    }
    line[num_chars++] = ')';
    line[num_chars] = '\0';
    fprintf(fout, "%s\n", line);
  }

  fclose(fout);

  return EXIT_SUCCESS;
}
