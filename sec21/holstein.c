/*
ID: mickeyj1
TASK: holstein
LANG: C
*/
#include <stdio.h>
#include <assert.h>

#define MAX_NUM_VITAMINS 25
#define MAX_NUM_FEEDS 15

/* returns 1 if the minimum requirements are met; 0 otherwise. */
int
is_enough(
  char* choices,
  int num_feeds_chosen,
  short feeds[][MAX_NUM_VITAMINS],
  short* requirements,
  int num_vitamins
) {
  int sum;
  int i, j;
  for (i = 0; i < num_vitamins; i++) {
    sum = 0;
    for (j = 0; j < num_feeds_chosen; j++) {
      sum += feeds[(int)choices[j]][i];
    }
    if (sum < requirements[i]) {
      return 0;
    }
  }
  return 1;
}

/* returns 1 if a solution is found; 0 otherwise. */
int
feed(
  int depth,
  int max_depth,
  int start,/* the feed to start with. */
  char* choices,
  int num_feeds,
  short feeds[][MAX_NUM_VITAMINS],
  int num_vitamins,
  short *requirements
) {
  if (depth == max_depth) {
    return is_enough(choices, depth, feeds, requirements, num_vitamins);
  }
  int r;
  int i;
  for (i = start; i < num_feeds; i++) {
    choices[depth] = i;
    r = feed(
      depth + 1,
      max_depth,
      i + 1,
      choices,
      num_feeds,
      feeds,
      num_vitamins,
      requirements
    );
    if (r) {
      return r;
    }
  }
  return 0;
}

int
main(int argc, char** argv) {
  short requirements[MAX_NUM_VITAMINS];
  short feeds[MAX_NUM_FEEDS][MAX_NUM_VITAMINS];
  char choices[MAX_NUM_FEEDS];
  int num_vitamins;
  int num_feeds;
  int i, j;

  FILE* fin = fopen("holstein.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d", &num_vitamins);
  for (i = 0; i < num_vitamins; i++) {
    fscanf(fin, "%hd", requirements + i);
  }
  fscanf(fin, "%d", &num_feeds);
  for (i = 0; i < num_feeds; i++) {
    for (j = 0; j < num_vitamins; j++) {
      fscanf(fin, "%hd", &feeds[i][j]);
    }
  }
  fclose(fin);

  int r;
  int num_feeds_chosen;
  for (i = 1; i <= num_feeds; i++) {
    r = feed(0, i, 0, choices, num_feeds, feeds, num_vitamins, requirements);
    if (r) {
      num_feeds_chosen = i;
      break;
    }
  }

  FILE* fout = fopen("holstein.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d", num_feeds_chosen);
  for (i = 0; i < num_feeds_chosen; i++) {
    fprintf(fout, " %d", choices[i] + 1);
  }
  fprintf(fout, "\n");
  fclose(fout);
  
  return 0;
}
