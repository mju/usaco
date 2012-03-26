/*
ID: mickeyj1
LANG: C
TASK: milk2
*/
#include <stdio.h>
#include <string.h>

#define N 999999

int
main(int argc, char** argv) {
  FILE* fin = fopen("milk2.in", "r");
  FILE* fout = fopen("milk2.out", "w");

  int n;
  int start, end;
  char intervals[N + 1];
  memset(intervals, 0, N);
  int max_end = 0;
  int min_start = N;
  for (fscanf(fin, "%d", &n); n > 0; n--) {
    fscanf(fin, "%d %d", &start, &end);
    if (end > max_end) {
      max_end = end;
    }
    if (start < min_start) {
      min_start = start;
    }
    for (; start < end; start++) {
      intervals[start] = 1;
    }
  }
  intervals[max_end] = 2;/* serves as a sentinel. */

  int max_milking = 0, max_idling = 0;
  int len ;
  int i;
  for (i = min_start, len = 1; i < max_end; i++, len++) {
    if (intervals[i] != intervals[i + 1]) {
      if (intervals[i] == 1) {
        if (len > max_milking) {
          max_milking = len;
        }
      } else {
        if (len > max_idling) {
          max_idling = len;
        }
      }
      len = 0;
    }
  }

  fprintf(fout, "%d %d\n", max_milking, max_idling);

  fclose(fin);
  fclose(fout);
  return 0;
}
