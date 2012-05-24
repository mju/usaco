/*
ID: mickeyj1
TASK: prefix
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_PRIMITIVES 200
#define MAX_LEN_PRIMITIVES 10
#define MAX_LEN_STR 200000

int
main(int argc, char** argv, char** envp) {
  char primitives[MAX_NUM_PRIMITIVES + 1][MAX_LEN_PRIMITIVES + 1];
  int len_primitives[MAX_NUM_PRIMITIVES];
  int min_len_primitives = MAX_LEN_PRIMITIVES;
  int num_primitives;
  char str[MAX_LEN_STR + 1];
  char is_possible[MAX_LEN_STR] = {0};
  int len_str = 0;
  int i, j;
  int max_len_prefix = 0;

  FILE* fin = fopen("prefix.in", "r");
  assert(fin != NULL);
  for (num_primitives = 0; 1; num_primitives++) {
    fscanf(fin, "%s", primitives[num_primitives]);
    if (strcmp(primitives[num_primitives], ".") == 0) {
      break;
    }
    len_primitives[num_primitives] = strlen(primitives[num_primitives]);
    if (len_primitives[num_primitives] < min_len_primitives) {
      min_len_primitives = len_primitives[num_primitives];
    }
  }
  while ((str[len_str] = (char)getc(fin)) != EOF) {
    if (str[len_str] >= 'A' && str[len_str] <= 'Z') {
      len_str++;
    }
  }
  fclose(fin);

  int idx;
  int initd = 0;
  for (i = 0; i < len_str - min_len_primitives; i++) {
    if (initd && !is_possible[i]) {
      continue;
    }
    idx = initd? i + 1: 0;
    for (j = 0; j < num_primitives; j++) {
      if (idx + len_primitives[j] > len_str) {
        continue;
      }
      if (strncmp(str + idx, primitives[j], len_primitives[j]) == 0) {
        is_possible[idx + len_primitives[j] - 1] = 1;
        if (idx + len_primitives[j] > max_len_prefix) {
          max_len_prefix = idx + len_primitives[j];
        }
      }
    }
    if (!initd) {
      initd = 1;
      i--;
    }
  }

  FILE* fout = fopen("prefix.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", max_len_prefix);
  fclose(fout);

  return EXIT_SUCCESS;
}
