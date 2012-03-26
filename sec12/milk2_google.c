/*
ID: mickeyj1
LANG: C
TASK: milk2
*/
#include <stdio.h>
#include <stdlib.h>

/* 1 <= N <= 5000 */
#define N 5000

struct interval {
  int start;
  int end;
};

int
cmp_interval(const struct interval* lhs, const struct interval* rhs) {
  return lhs->start - rhs->start;
}

int
main(int argc, char** argv) {
  FILE* fin = fopen("milk2.in", "r");
  FILE* fout = fopen("milk2.out", "w");

  int i;
  int n;
  int start, end;
  struct interval intervals[N];

  fscanf(fin, "%d", &n);
  for (i = 0; i < n; i++) {
    fscanf(fin, "%d %d", &start, &end);
    intervals[i].start = start;
    intervals[i].end = end;
  }

  qsort(
    intervals,
    n,
    sizeof(struct interval),
    (int (*)(const void*, const void*))cmp_interval
  );

  int max_covered_interval = 0;
  int max_uncovered_interval = 0;
  start = intervals[0].start;
  end = intervals[0].end;
  int tmp;
  for (i = 1; i < n; i++) {
    if (intervals[i].start > end) {
      tmp = end - start;
      if (tmp > max_covered_interval) {
        max_covered_interval = tmp;
      }
      tmp = intervals[i].start - end;
      if (tmp > max_uncovered_interval) {
        max_uncovered_interval = tmp;
      }
      start = intervals[i].start;
      end = intervals[i].end;
    } else {
      if (intervals[i].end > end) {
        end = intervals[i].end;
      }
    }
  }

  tmp = end - start;
  if (tmp > max_covered_interval) {
    max_covered_interval = tmp;
  }

  fprintf(fout, "%d %d\n", max_covered_interval, max_uncovered_interval);

  fclose(fin);
  fclose(fout);
  return 0;
}
