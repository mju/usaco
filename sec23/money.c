/*
ID: mickeyj1
TASK: money
LANG: C
*/
#include <stdio.h>
#include <assert.h>

#define MAX_AMOUNT 10000
#define MAX_NUM_COINS 25

int
main(int argc, char** argv, char** envp) {
  int num_coins;
  int amount;
  int coins[MAX_NUM_COINS];
  long long amounts[MAX_AMOUNT + 1] = {0};
  int i;
  FILE* fin = fopen("money.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d %d", &num_coins, &amount);
  for (i = 0; i < num_coins; i++) {
    fscanf(fin, "%d", coins + i);
  }
  fclose(fin);

  amounts[0] = 1;
  int j;
  for (i = 0; i < num_coins; i++) {
    for (j = 1; j <= amount; j++) {
      amounts[j] += (j - coins[i] >= 0)? amounts[j - coins[i]]: 0;
    }
  }

  FILE* fout = fopen("money.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%lld\n", amounts[amount]);
  fclose(fout);

  return 0;
}
