/*
ID: mickeyj1
LANG: C++
TASK: palsquare
*/
#include <stdio.h>

#define N 300
#define LEN_BUF 19/* 2 * log_2(300) + 1 */

void
reversed_num_w_base(int num, int base, char* buf) {
  int pos_buf = 0;
  while (num) {
    int remainder = num % base;
    buf[pos_buf++] = (remainder >= 10)? remainder - 10 + 'A': remainder + '0';
    num /= base;
  }
  buf[pos_buf] = '\0';
}

int
is_palindromic(char* s) {
  int len;
  for (len = 0; s[len] != '\0'; len++)
    ;
  int half_len = len >> 1;
  len--;
  int i;
  for (i = 0; i < half_len; i++) {
    if (s[i] != s[len - i]) {
      return 0;
    }
  }
  return 1;
}

int
main(int argc, char** argv) {
  FILE* fin = fopen("palsquare.in", "r");
  int base;
  fscanf(fin, "%d", &base);
  fclose(fin);

  FILE* fout = fopen("palsquare.out", "w");

  char buf[LEN_BUF + 1];
  char num[LEN_BUF + 1];

  int i;
  for (i = 1; i <= N; i++) {
    int square = i * i;
    reversed_num_w_base(square, base, buf);
    if (is_palindromic(buf)) {
      reversed_num_w_base(i, base, num);
      int len;
      for (len = 0; num[len] != '\0'; len++)
        ;
      for (len--; len >=0; len--) {
        fprintf(fout, "%c", num[len]);
      }
      fprintf(fout, " %s\n", buf);
    }
  }

  fclose(fout);

  return 0;
}
