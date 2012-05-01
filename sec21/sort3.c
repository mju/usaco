/*
ID: mickeyj1
TASK: sort3
LANG: C
*/
#include <stdio.h>
#include <assert.h>

#define MAX_NUM_NUMS 1000

int
main(int argc, char** argv) {
  int num_nums;
  int nums[MAX_NUM_NUMS];
  int min_num_swaps = 0;
  int first_two = 0, first_three = 0;
  int i, j;

  FILE* fin = fopen("sort3.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d", &num_nums);
  for (i = 0; i < num_nums; i++) {
    fscanf(fin, "%d", nums + i);
  }
  fclose(fin);

  for (i = 0; i < num_nums; i++) {
    switch (nums[i]) {
      case 2: first_two++; break;
      case 3: first_three++; break;
    }
  }
  first_two = num_nums - first_two - first_three;
  first_three = num_nums - first_three;

  for (i = 0; i < first_two; i++) {
    if (nums[i] != 1) {
      min_num_swaps++;
      if (nums[i] == 2) {
        for (j = first_two; j < first_three; j++) {
          if (nums[j] == 1) {
            nums[i] = 1;
            nums[j] = 2;
            break;
          }
        }
        if (nums[i] == 2) {
          for (j = first_three; j < num_nums; j++) {
            if (nums[j] == 1) {
              nums[i] = 1;
              nums[j] = 2;
              break;
            }
          }
        }
      } else if (nums[i] == 3) {
        for (j = first_three; j < num_nums; j++) {
          if (nums[j] == 1) {
            nums[i] = 1;
            nums[j] = 3;
            break;
          }
        }
        if (nums[i] == 3) {
          for (j = first_two; j < first_three; j++) {
            if (nums[j] == 1) {
              nums[i] = 1;
              nums[j] = 3;
              break;
            }
          }
        }
      }
    }
  }

  for (i = first_two; i < first_three; i++) {
    if (nums[i] == 3) {
      min_num_swaps++;
      for (j = first_three; j < num_nums; j++) {
        if (nums[j] == 2) {
          nums[i] = 2;
          nums[j] = 3;
          break;
        }
      }
    }
  }

  FILE* fout = fopen("sort3.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", min_num_swaps);
  fclose(fout);

  return 0;
}
