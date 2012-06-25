/*
ID: mickeyj1
TASK: kimbits
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_LEN_STR 31

void
print_lld_b(long long target, int len_str, FILE* fout) {
  if (len_str == 0) {
    return;
  }
  print_lld_b(target >> 1, len_str - 1, fout);
  fprintf(fout, "%lld", target & 0x1);
}

int
main(int argc, char** argv, char** envp) {
  int len_str;
  int max_num_ones;
  long long target;
  long long targeted_value = 0;
  /* dp_tbl[i][L] denotes how many strings are there with no more than L bits
   * being one when the ith digit(count from the right) is one and all digits
   * to the left are zeros.
   */
  int dp_tbl[MAX_LEN_STR][MAX_LEN_STR + 1];
  int i, j, k;
  long long num_strs;

  FILE* fin = fopen("kimbits.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d%d%lld", &len_str, &max_num_ones, &target);
  fclose(fin);

  for (i = 1; i <= max_num_ones; i++) {
    dp_tbl[0][i] = 1;
  }
  for (i = 0; i < len_str; i++) {
    dp_tbl[i][0] = 0;
  }
  for (i = 1; i < len_str; i++) {
    for (j = 1; j <= max_num_ones; j++) {
      dp_tbl[i][j] = 1;/* zero always counts */
      for (k = 0; k < i; k++) {
        dp_tbl[i][j] += dp_tbl[k][j - 1];
      }
    }
  }

  /* get the desired value. */
  for (i = max_num_ones; i >= 0 && target; i--, target -= num_strs) {
    num_strs = 1;/* zero. */
    for (j = 0; j < len_str; j++) {
      if (num_strs + dp_tbl[j][i] >= target) {
        if (num_strs == target) {
          if (j > 0) {/* when j is zero, zero is the result for this round. */
            targeted_value |= 1 << (j - 1);
          }
        } else {
          targeted_value |= 1 << j;
        }
        break;
      }
      num_strs += dp_tbl[j][i];
    }
    /* the target is not possible. */
    if (j == len_str) {
      targeted_value = -1;
      break;
    }
  }

  if (targeted_value >= 0) {
    FILE* fout = fopen("kimbits.out", "w");
    assert(fout != NULL);
    print_lld_b(targeted_value, len_str, fout);
    fprintf(fout, "\n");
    fclose(fout);
  }

  return EXIT_SUCCESS;
}
