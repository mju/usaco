/*
ID: mickeyj1
TASK: runround
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/* checks if num is a runaround number.  num should contain only unique
 * digits without zeros.
 * returns one on success, zero otherwise.
 */
int
is_runaround_num(char* num, int num_digits) {
  int idx = 0;
  char tbl[9] = {0};
  int i;
  for (i = 0; i < num_digits; i++) {
    idx = (idx + num[idx]) % num_digits;
    if (tbl[idx] == 1 || (idx == 0 && i < num_digits - 1)) {
      return 0;
    }
    tbl[idx] = 1;
  }
  return 1;
}

int
a_to_i(char* num, int num_digits) {
  int r = num[0];
  int i;
  for (i = 1; i < num_digits; i++) {
    r = r * 10 + num[i];
  }
  return r;
}

/* returns one if found, zero otherwise. next_num holds the result. */
int
_next_runaround_num(
  int* first_run, int depth, int len, char* next_num, char* start, char* marks
) {
  if (depth == len) {
    if (start != NULL && *first_run == 1) {
      *first_run = 0;
    }
    return is_runaround_num(next_num, len);
  }
  int i = (start != NULL && *first_run && start[depth])? start[depth]: 1;
  for (; i <= 9; i++) {
    if (marks[i]) {
      continue;
    }
    next_num[depth] = i;
    marks[i] = 1;
    if (
      _next_runaround_num(first_run, depth + 1, len, next_num, start, marks)
    ) {
      return 1;
    }
    marks[i] = 0;
  }
  return 0;
}

int
next_runaround_num(int num) {
  int i;
  char tbl[9 + 1];
  int len;

  sprintf(tbl, "%d", num);
  len = strlen(tbl);
  for (i = 0; i < len; i++) {
    tbl[i] -= '0';
  }

  int first_run = 1;
  char next_num[9];
  char marks[10] = {0};
  if (_next_runaround_num(&first_run, 0, len, next_num, tbl, marks)) {
    return a_to_i(next_num, len);
  }
  for (i = len + 1; i <= 9; i++) {
    if (_next_runaround_num(&first_run, 0, len, next_num, NULL, marks)) {
      return a_to_i(next_num, len);
    }
  }
  return -1;
}

int
main(int argc, char** argv, char** envp) {
  int num;

  FILE* fin = fopen("runround.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d", &num);
  fclose(fin);

  FILE* fout = fopen("runround.out", "w");
  assert(fout != NULL);
  int r = next_runaround_num(num + 1);
  if (r != -1) {
    fprintf(fout, "%d\n", r);
  }
  fclose(fout);

  return EXIT_SUCCESS;
}
