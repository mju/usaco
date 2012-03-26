/*
ID: mickeyj1
LANG: C
TASK: crypt1
*/
#include <stdio.h>
#include <assert.h>

#define BOUND_PARTIAL_PRODUCT 1000
#define BOUND_PRODUCT 10000
#define DIVIDE 100
#define NUM_DIGITS 10
#define DEPTH 5

int
is_valid(int num, char* digits_allowed) {
  if (num == 0) {
    return 1;
  }
  return digits_allowed[num % 10] && is_valid(num / 10, digits_allowed);
}

void
backtrack(int depth, char* digits_allowed, int* num, int* num_sols) {
  if (depth == DEPTH) {
    int n0 = *num / DIVIDE;
    int n1 = *num % DIVIDE;
    int partial_product0 = n0 * (n1 % 10);
    int partial_product1 = n0 * (n1 / 10);
    int product = n0 * n1;
    if (
      partial_product0 >= BOUND_PARTIAL_PRODUCT ||
      !is_valid(partial_product0, digits_allowed) ||
      partial_product1 >= BOUND_PARTIAL_PRODUCT ||
      !is_valid(partial_product1, digits_allowed) ||
      product >= BOUND_PRODUCT ||
      !is_valid(product, digits_allowed)
    ) {
      return;
    }
    *num_sols = *num_sols + 1;
    return;
  }

  int i;
  for (i = 1; i < NUM_DIGITS; i++) {
    if (digits_allowed[i]) {
      *num = *num * 10 + i;
      backtrack(depth + 1, digits_allowed, num, num_sols);
      *num = *num / 10;
    }
  }
}

int
main(int argc, char** argv) {
  int n;
  char digits_allowed[NUM_DIGITS] = {0};

  FILE* fin = fopen("crypt1.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d", &n);
  int i;
  int digit;
  for (i = 0; i < n; i++) {
    fscanf(fin, "%d", &digit);
    digits_allowed[digit] = 1;
  }
  fclose(fin);

  int num_sols = 0;
  int num = 0;
  backtrack(0, digits_allowed, &num, &num_sols);

  FILE* fout = fopen("crypt1.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", num_sols);
  fclose(fout);

  return 0;
}
