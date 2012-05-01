/*
ID: mickeyj1
TASK: frac1
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_DEN 160

struct frac {
  short num;
  short den;
};

int
cmp_frac(const struct frac* lhs, const struct frac* rhs) {
  return lhs->num * rhs->den - rhs->num * lhs->den;
}

int
cmp_frac_qsort(const struct frac* lhs, const struct frac* rhs) {
  int r = cmp_frac(lhs, rhs);
  if (r != 0) {
    return r;
  }
  return lhs->den - rhs->den;
}

int
main(int argc, char** argv) {
  int max_den;
  FILE* fin = fopen("frac1.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d", &max_den);
  fclose(fin);

  struct frac fracs[((MAX_DEN + 3) * MAX_DEN) >> 1];

  int num_fracs = 0;
  int i, j;
  for (i = 1; i <= max_den; i++) {
    for (j = 0; j <= i; j++) {
      fracs[num_fracs].den = i;
      fracs[num_fracs].num = j;
      num_fracs++;
    }
  }

  qsort(
    fracs,
    num_fracs,
    sizeof(fracs[0]),
    (int(*)(const void*, const void*))cmp_frac_qsort
  );

  
  FILE* fout = fopen("frac1.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d/%d\n", fracs[0].num, fracs[0].den);
  for (i = 1, j = 0; i < num_fracs; i++) {
    if (cmp_frac(fracs + i, fracs + j) == 0) {
      continue;
    }
    fprintf(fout, "%d/%d\n", fracs[i].num, fracs[i].den);
    j = i;
  }

  fclose(fout);
  
  return 0;
}
