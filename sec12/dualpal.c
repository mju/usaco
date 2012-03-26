/*
ID: mickeyj1
LANG: C
TASK: dualpal
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define LEN_BUF 32/* log_2(2^32) */

int
is_palindromic(char* buf) {
  char* _buf;
  for (_buf = buf + strlen(buf) - 1; buf < _buf; buf++, _buf--) {
    if (*buf != *_buf) {
      return 0;
    }
  }
  return 1;
}

int
main(int argc, char** argv) {
  int n, s;
  FILE* fin = fopen("dualpal.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d %d", &n, &s);
  fclose(fin);

  FILE* fout = fopen("dualpal.out", "w");
  assert(fout != NULL);

  char buf[LEN_BUF + 1];
  int num_bases;
  int base;
  for (s++; n > 0; s++) {
    for (num_bases = 0, base = 2; base <= 10; base++) {
      int num = s;
      int pos_buf = 0;
      while (num) {
        buf[pos_buf++] = num % base + '0';
        num /= base;
      }
      buf[pos_buf] = '\0';
      if (is_palindromic(buf)) {
        num_bases++;
        if (num_bases == 2) {
          n--;
          fprintf(fout, "%d\n", s);
          break;
        }
      }
    }
  }
  fclose(fout);

  return 0;
}
