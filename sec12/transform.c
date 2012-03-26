/*
ID: mickeyj1
LANG: C
TASK: transform
*/
#include <stdio.h>

#define N 10

int
rotate_ninety(int n, char before[][N + 1], char after[][N + 1]) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (before[i][j] != after[j][n - 1 - i]) {
        return 0;
      }
    }
  }
  return 1;
}

int
rotate_one_eighty(int n, char before[][N + 1], char after[][N + 1]) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (before[i][j] != after[n - 1 - i][n - 1 - j]) {
        return 0;
      }
    }
  }
  return 1;
}

int
rotate_two_seventy(int n, char before[][N + 1], char after[][N + 1]) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (before[i][j] != after[n - 1 - j][i]) {
        return 0;
      }
    }
  }
  return 1;
}

int
reflect_horizontally(int n, char before[][N + 1], char after[][N + 1]) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (before[i][j] != after[i][n - 1 - j]) {
        return 0;
      }
    }
  }
  return 1;
}

int
combination(int n, char before[][N + 1], char after[][N + 1]) {
  int r = 1;
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (before[i][j] != after[n - 1 -j][n - 1 - i]) {
        r = 0;
        break;
      }
    }
  }

  if (r == 1) {
    return r;
  }
  r = 1;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (before[i][j] != after[n - 1 - i][j]) {
        r = 0;
        break;
      }
    }
  }

  if (r == 1) {
    return r;
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (before[i][j] != after[j][i]) {
        return 0;
      }
    }
  }

  return 1;
}

int
no_change(int n, char before[][N + 1], char after[][N + 1]) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (before[i][j] != after[i][j]) {
        return 0;
      }
    }
  }
  return 1;
}

int
transform(int n, char before[][N + 1], char after[][N + 1]) {
  int r;
  if (rotate_ninety(n, before, after)) {
    r = 1;
  } else if (rotate_one_eighty(n, before, after)) {
    r = 2;
  } else if (rotate_two_seventy(n, before, after)) {
    r = 3;
  } else if (reflect_horizontally(n, before, after)) {
    r = 4;
  } else if (combination(n, before, after)) {
    r = 5;
  } else if (no_change(n, before, after)) {
    r = 6;
  } else {
    r = 7;
  }
  return r;
}

int
main(int argc, char** argv) {
  FILE* fin = fopen("transform.in", "r");
  FILE* fout = fopen("transform.out", "w");

  int n;
  fscanf(fin, "%d", &n);

  char before[N][N + 1];
  char after[N][N + 1];

  int i;
  for (i = 0; i < n; i++) {
    fscanf(fin, "%s", before[i]);
  }
  for (i = 0; i < n; i++) {
    fscanf(fin, "%s", after[i]);
  }

  fprintf(fout, "%d\n", transform(n, before, after));

  fclose(fin);
  fclose(fout);
  return 0;
}
