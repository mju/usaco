/*
ID: mickeyj1
LANG: C
TASK: pprime
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>

/* since sqart(100,000,000) == 10,000 */
#define N 4999
#define NOT_A_PRIME 0
#define IS_A_PRIME 1
#define MAX_NUM_DIGITS 9
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
  if (num == 2) {
    return IS_A_PRIME;
  }
  if ((num & 0x1) == 0) {
    return NOT_A_PRIME;
  }
  if ( num <= ((n - 1) << 1) + 3) {
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

int
num_digits(int d) {
  int r = 0;
  while (d) {
    r++;
    d /= 10;
  }
  return r;
}

int
pow_ten(int p) {
  int r = 1;
  int i;
  for (i = 0; i < p; i++) {
    r *= 10;
  }
  return r;
}

int
get_palindrome(int d, int num_digits) {
  int _d = d;
  if ((num_digits & 0x1) == 1) {
    _d /= 10;
  }
  while (_d) {
    d = d * 10 + _d % 10;
    _d /= 10;
  }
  return d;
}

int
main(int argc, char** argv) {
  char sieve[N];
  get_primes(sieve, N);

  FILE* fin = fopen("pprime.in", "r");
  assert(fin != NULL);
  int lower, upper;
  fscanf(fin, "%d %d", &lower, &upper);
  fclose(fin);

  FILE* fout = fopen("pprime.out", "w");
  assert(fout != NULL);

  int digit;
  int digit_lower = num_digits(lower);
  int digit_upper = num_digits(upper);
  int ceiling;
  int ceiling_x_ten;
  int palindrome;
  int i;
  for (digit = digit_lower; digit <= digit_upper; digit++) {
    ceiling = (digit >> 1) + (digit & 0x1);
    if (digit == digit_lower) {
      i = lower / (pow_ten(digit_lower >> 1));
      ceiling_x_ten = pow_ten(ceiling);
    } else {
      i = pow_ten(ceiling - 1);
      ceiling_x_ten = i * 10;
    }
    for (; i < ceiling_x_ten; i++) {
      palindrome = get_palindrome(i, digit);
      if (IS_PRIME(palindrome) && palindrome >= lower && palindrome <= upper) {
        fprintf(fout, "%d\n", palindrome);
      } else if (palindrome > upper) {
        break;
      }
    }
  }

  fclose(fout);

  return 0;
}
