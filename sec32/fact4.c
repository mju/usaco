/*
ID: mickeyj1
TASK: fact4
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int
last_nonzero_digit(int num) {
  int i;
  int tmp;
  int num_twos = 0;
  int last_digit = 1;

  for (i = 2; i <= num; i++) {
    tmp = i;
    while ((tmp & 0x1) == 0) {
      num_twos++;
      tmp >>= 1;
    }
    while (tmp % 5 == 0) {
      num_twos--;
      tmp /= 5;
    }
    last_digit *= tmp;
    last_digit %= 10;
  }

  if (num_twos > 0) {
    last_digit <<= (num_twos & 0x3) == 0? 4: (num_twos & 0x3); 
    last_digit %= 10;
  }

  return last_digit;
}

int
main(int argc, char** argv, char** envp) {
  int num;
  FILE* fin = fopen("fact4.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d", &num);
  fclose(fin);

  FILE* fout = fopen("fact4.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", last_nonzero_digit(num));
  fclose(fout);

  return EXIT_SUCCESS;
}
