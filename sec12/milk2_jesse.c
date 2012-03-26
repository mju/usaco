/*
ID: mickeyj1
LANG: C
TASK: milk2
*/
#include <stdio.h>
#include <stdlib.h>

/* 1 <= N <= 5000 */
#define N 5000

struct an_end {
  int timing;
  char is_start;
};

int
cmp_an_end(const struct an_end* lhs, const struct an_end* rhs) {
  if (lhs->timing != rhs->timing) {
    return lhs->timing - rhs->timing;
  }
  /* start points go first. */
  return rhs->is_start - lhs->is_start;
}

int
main(int argc, char** argv) {
  FILE* fin = fopen("milk2.in", "r");
  FILE* fout = fopen("milk2.out", "w");

  int i;
  int n;
  int start, end;
  struct an_end ends[N << 1];

  fscanf(fin, "%d", &n);
  for (i = 0; i < n; i++) {
    fscanf(fin, "%d %d", &start, &end);
    int pos = i << 1;
    ends[pos].timing = start;
    ends[pos].is_start = 1;
    ends[pos + 1].timing = end;
    ends[pos + 1].is_start = 0;
  }

  int num_ends = n << 1;
  qsort(
    ends,
    num_ends,
    sizeof(struct an_end),
    (int (*)(const void*, const void*))cmp_an_end
  );

  int num_open_intervals = 1;
  /* keeps track of either the start or the end of a coverd interval. */
  int timing = ends[0].timing;
  int max_covered_interval = 0;
  int max_uncovered_interval = 0;
  for (i = 1; i < num_ends; i++) {
    if (ends[i].is_start) {
      if (num_open_intervals == 0) {
        timing = ends[i].timing - timing;
        if (timing > max_uncovered_interval) {
          max_uncovered_interval = timing;
        }
        timing = ends[i].timing;
      }
      num_open_intervals++;
    } else {
      num_open_intervals--;
      if (num_open_intervals == 0) {
        timing = ends[i].timing - timing;
        if (timing > max_covered_interval) {
          max_covered_interval = timing;
        }
        timing = ends[i].timing;
      }
    }
  }

  fprintf(fout, "%d %d\n", max_covered_interval, max_uncovered_interval);

  fclose(fin);
  fclose(fout);
  return 0;
}
