/*
ID: mickeyj1
TASK: humble
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_NUM_HUMBLE_NUMS 100000
#define MAX_NUM_PRIMES 100

/* returns the index such that nums[index] >= target.  -1 is returns if
 * no such a number. */
int
binary_search(int* nums, int l, int r, int target) {
  if (l == r) {
    if (nums[l] >= target) {
      return l;
    }
    return -1;
  }
  int mid = (l + r) >> 1;
  if (nums[mid] == target) {
    return mid;
  }
  if (nums[mid] < target) {
    return binary_search(nums, mid + 1, r, target);
  } else {
    return binary_search(nums, l, mid, target);
  }
}

int
main(int argc, char** argv, char** envp) {
  int num_primes;
  int primes[MAX_NUM_PRIMES];
  int num_humble_nums;
  int humble_nums[MAX_NUM_HUMBLE_NUMS + 1];
  int target;
  int min;
  int i, j;

  FILE* fin = fopen("humble.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d %d", &num_primes, &num_humble_nums);
  for (i = 0; i < num_primes; i++) {
    fscanf(fin, "%d", primes + i);
  }
  fclose(fin);

  humble_nums[0] = 1;
  for (i = 1; i <= num_humble_nums; i++) {
    min = -1;
    for (j = 0; j < num_primes; j++) {
      target = (humble_nums[i - 1] + 1) / primes[j];
      if (target * primes[j] < humble_nums[i - 1] + 1) {
        target++;/* take floor. */
      }
      /* find the min humble number N so that N * primes[j] is greater than the
       * last humble number.  Run binary search to improve runtime.
       */
      int idx = binary_search(humble_nums, 0, i - 1, target);
      assert(idx != -1);
      target = humble_nums[idx] * primes[j];
      if (min == - 1 || target < min) {
        min = target;
      }
    }
    humble_nums[i] = min;
  }

  FILE* fout = fopen("humble.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", humble_nums[num_humble_nums]);
  fclose(fout);

  return EXIT_SUCCESS;
}
