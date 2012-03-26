/*
ID: mickeyj1
LANG: C
TASK: milk
*/
#include <stdio.h>
#include <assert.h>

#define N 1001
#define M 2000000

int
main(int argc, char** argv) {
  int amt_milk_wanted;
  int num_farmers;
  FILE* fin = fopen("milk.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d %d", &amt_milk_wanted, &num_farmers);

  int price_amount[N] = {0};
  int price;
  int amount;
  int i;
  for (i = 0; i < num_farmers; i++) {
    fscanf(fin, "%d %d", &price, &amount);
    int tmp = price_amount[price] + amount;
    price_amount[price] = tmp >= M? M: tmp;
  }

  int min_cost = 0;
  for (price = 0; price < N && amt_milk_wanted > 0; price++) {
    amount = price_amount[price] > amt_milk_wanted?
      amt_milk_wanted: price_amount[price];
    min_cost += price * amount;
    amt_milk_wanted -= amount;
  }

  FILE* fout = fopen("milk.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", min_cost);
  fclose(fout);

  return 0;
}
