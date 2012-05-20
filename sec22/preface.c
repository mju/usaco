/*
ID: mickeyj1
TASK: preface
LANG: C
*/
#include <stdio.h>
#include <assert.h>

int
main(int argc, char** argv) {
  char chars[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
  int result[7] = {0};
  int table[4][10][7] = {
    {{0},{1,0,0,0,0,0,0},{2,0,0,0,0,0,0},{3,0,0,0,0,0,0},{1,1,0,0,0,0,0},{0,1,0,0,0,0,0},{1,1,0,0,0,0,0},{2,1,0,0,0,0,0},{3,1,0,0,0,0,0},{1,0,1,0,0,0,0}},
    {{0},{0,0,1,0,0,0,0},{0,0,2,0,0,0,0},{0,0,3,0,0,0,0},{0,0,1,1,0,0,0},{0,0,0,1,0,0,0},{0,0,1,1,0,0,0},{0,0,2,1,0,0,0},{0,0,3,1,0,0,0},{0,0,1,0,1,0,0}},
    {{0},{0,0,0,0,1,0,0},{0,0,0,0,2,0,0},{0,0,0,0,3,0,0},{0,0,0,0,1,1,0},{0,0,0,0,0,1,0},{0,0,0,0,1,1,0},{0,0,0,0,2,1,0},{0,0,0,0,3,1,0},{0,0,0,0,1,0,1}},
    {{0},{0,0,0,0,0,0,1},{0,0,0,0,0,0,2},{0,0,0,0,0,0,3},{0},{0},{0},{0},{0},{0}}
  };

  int num_pages;
  FILE* fin = fopen("preface.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d", &num_pages);
  fclose(fin);

  int i;
  int tens;
  int tmp;
  int digit;
  int page;
  for (page = 1; page <= num_pages; page++) {
    tens = 0;
    tmp = page;
    while (tmp) {
      digit = tmp % 10;
      for (i = 0; i < 7; i++) {
        result[i] += table[tens][digit][i];
      }
      tmp /= 10;
      tens++;
    }
  }

  FILE* fout = fopen("preface.out", "w");
  assert(fout != NULL);
  for (i = 0; i < 7; i++) {
    if (result[i] > 0) {
      fprintf(fout, "%c %d\n", chars[i], result[i]);
    }
  }
  fclose(fout);

  return 0;
}
