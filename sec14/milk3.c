/*
ID: mickeyj1
LANG: C
TASK: milk3
*/
#include<stdio.h>
#include<assert.h>

#define MAX 20

void
pour(int* _src, int* _dest, int dest) {
  int capacity_dest = dest - *_dest;
  if (*_src <= capacity_dest) {
    *_dest = *_dest + *_src;
    *_src = 0;
  } else {
    *_src = *_src - capacity_dest;
    *_dest = dest;
  }
}

/*
 * given x could be a, b or c, x denotes the capacity,
 * _x denotes how full it is currently.
 */
void
backtrack(
  int _a, int a, int _b, int b, int _c, int c,
  char* possible_c, char marks[][MAX + 1][MAX + 1]
) {
  if (marks[_a][_b][_c] == 1) {
    return;
  }
  marks[_a][_b][_c] = 1;
  if (_a == 0) {
    possible_c[_c] = 1;
  }

  /* do all possible moves */
  int tmp_a, tmp_b, tmp_c = c;
  /* a -> b */
  tmp_a = _a, tmp_b = _b, tmp_c = _c;
  pour(&tmp_a, &tmp_b, b);
  backtrack(tmp_a, a, tmp_b, b, tmp_c, c, possible_c, marks);
  /* a -> c */
  tmp_a = _a, tmp_b = _b, tmp_c = _c;
  pour(&tmp_a, &tmp_c, c);
  backtrack(tmp_a, a, tmp_b, b, tmp_c, c, possible_c, marks);
  /* b -> a */
  tmp_a = _a, tmp_b = _b, tmp_c = _c;
  pour(&tmp_b, &tmp_a, a);
  backtrack(tmp_a, a, tmp_b, b, tmp_c, c, possible_c, marks);
  /* b -> c */
  tmp_a = _a, tmp_b = _b, tmp_c = _c;
  pour(&tmp_b, &tmp_c, c);
  backtrack(tmp_a, a, tmp_b, b, tmp_c, c, possible_c, marks);
  /* c -> a */
  tmp_a = _a, tmp_b = _b, tmp_c = _c;
  pour(&tmp_c, &tmp_a, a);
  backtrack(tmp_a, a, tmp_b, b, tmp_c, c, possible_c, marks);
  /* c -> b */
  tmp_a = _a, tmp_b = _b, tmp_c = _c;
  pour(&tmp_c, &tmp_b, b);
  backtrack(tmp_a, a, tmp_b, b, tmp_c, c, possible_c, marks);
}

int
main(int argc, char** argv) {
  FILE* fin = fopen("milk3.in", "r");
  assert(fin != NULL);
  int a, b, c;
  fscanf(fin, "%d %d %d", &a, &b, &c);
  fclose(fin);

  char possible_c[MAX + 1] = {0};
  char marks[MAX + 1][MAX + 1][MAX + 1] = {{{0}}};
  backtrack(0, a, 0, b, c, c, possible_c, marks);

  FILE* fout = fopen("milk3.out", "w");
  assert(fout != NULL);
  int i;
  char* format = "%d";
  for (i = 0; i < MAX + 1; i++) {
    if (possible_c[i] == 1) {
      fprintf(fout, format, i);
      format = " %d";
    }
  }
  fprintf(fout, "\n");
  fclose(fout);

  return 0;
}
