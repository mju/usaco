/*
ID: mickeyj1
TASK: hamming
LANG: C
*/
#include <stdio.h>
#include <assert.h>

#define MAX_NUM_BITS 8
#define MARK -1

int
hamming_dist(int lhs, int rhs) {
  if (lhs == rhs) {
    return 0;
  }
  int xored = lhs ^ rhs;
  int r = 0;
  int i;
  for (i = 0; i <= 7; i++) {
    if ((xored & (1 << i)) != 0) {
      r++;
    }
  }
  return r;
}

int
backtrack(int depth, int start, int size_set, int dist, short* nums, int num_nums, short* sol) {
  int i;
  if (depth == size_set) {
    return 1;
  }
  int j;
  int valid;
  for (i = start; i < num_nums; i++) {
    valid = 1;
    for (j = 0; j < depth; j++) {
      if (hamming_dist(nums[i], sol[j]) < dist) {
        valid = 0;
        break;
      }
    }
    if (valid == 1) {
      sol[depth] = nums[i];
      if (backtrack(depth + 1, i + 1, size_set, dist, nums, num_nums, sol)) {
        return 1;
      }
    }
  }
  return 0;
}

int
main(int argc, char** argv) {
  int size_set;
  int num_bits;
  int dist;
  short nums[1 << MAX_NUM_BITS];
  short sol[1 << MAX_NUM_BITS];
  int i;

  FILE* fin = fopen("hamming.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d%d%d", &size_set, &num_bits, &dist);
  fclose(fin);

  int bound = 1 << num_bits;
  int num_nums = 0;
  for (i = 1; i < bound; i++) {
    if (hamming_dist(0, i) >= dist) {
      nums[num_nums++] = i;
    }
  }

  FILE* fout = fopen("hamming.out", "w");
  assert(fout != NULL);

  sol[0] = 0;
  if (backtrack(1, 0, size_set, dist, nums, num_nums, sol)) {
    for (i = 0; i < size_set; i++) {
      if (i > 0) {
        if (i % 10 == 0) {
          fprintf(fout, "\n");
        } else {
          fprintf(fout, " ");
        }
      }
      fprintf(fout, "%hd", sol[i]);
    }
    fprintf(fout, "\n");
  }

  fclose(fout);

  return 0;
}
