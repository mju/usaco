/*
ID: mickeyj1
LANG: C
TASK: sprime
*/
/* WARNING: this code is not well-written, please do better. */
/* or go to the analysis page on usaco site to see what's wrong. */
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define N 1000000
#define NOT_A_PRIME 0
#define IS_A_PRIME 1
#define IS_PRIME(X) is_prime(sieve, N, X)

/*
 * @param sieve an array used to indicate if 2 * index + 3 is a prime
 *  number or not.
 * @param n, the number of elements of the array.
 */
void
get_primes(char* sieve, int n) {
  assert(n <= N);
  int i;
  for (i = 0; i < n; i++) {
    sieve[i] = IS_A_PRIME;
  }

  /* take some example to see why floor(n / 2) can be use to bound. */
  /* or do the math to see that. */
  int j;
  int prime;
  int half_n = n >> 1;
  for (i = 0; i < half_n; i++) {
    if (sieve[i] == IS_A_PRIME) {
      /* remove the multiples of sieve[i], do the math to see why
       * the indexes are those used.
       */
      prime = i + i + 3;
      for (j = prime + i; j < n; j += prime) {
        sieve[j] = NOT_A_PRIME;
      }
    }
  }
}

int
is_prime(char* sieve, int n, int num) {
  if (num < 2) {
    return NOT_A_PRIME;
  }
  if (num == 2) {
    return IS_A_PRIME;
  }
  if ((num & 0x1) == 0) {
    return NOT_A_PRIME;
  }
  if (num <= ((n - 1) << 1) + 3) {
    return sieve[(num - 3) >> 1];
  }
  int sq_root = (int)sqrt((double)num);
  int prime;
  int i;
  for (i = 0; i < n; i++) {
    prime = i + i + 3;
    if (prime > sq_root) {
      break;
    }
    if (sieve[i] == IS_A_PRIME) {
      if (num % prime == 0) {
        return NOT_A_PRIME;
      }
    }
  }
  return IS_A_PRIME;
}

void
backtrack(int n, int num_digits, int* d, char* sieve, FILE* fout) {
  if (n == num_digits) {
    fprintf(fout, "%d\n", *d);
  }
  int tmp;
  int i;

  tmp = *d;
  *d = *d * 10 + 1;
  if (IS_PRIME(*d)) {
    backtrack(n + 1, num_digits, d, sieve, fout);
  }
  *d = tmp;

  if (n == 0) {
    tmp = *d;
    *d = *d * 10 + 2;
    if (IS_PRIME(*d)) {
      backtrack(n + 1, num_digits, d, sieve, fout);
    }
    *d = tmp;
  }

  for (i = 3; i < 10; i += 2) {
    tmp = *d;
    *d = *d * 10 + i;
    if (IS_PRIME(*d)) {
      backtrack(n + 1, num_digits, d, sieve, fout);
    }
    *d = tmp;
  }
}

int
main(int argc, char** argv) {
  char sieve[N];
  get_primes(sieve, N);

  FILE* fin = fopen("sprime.in", "r");
  assert(fin != NULL);
  int num_digits;
  fscanf(fin, "%d", &num_digits);
  fclose(fin);

  FILE* fout = fopen("sprime.out", "w");
  assert(fout != NULL);
  int d = 0;
  backtrack(0, num_digits, &d, sieve, fout);
  fclose(fout);

  return 0;
}
