/*
ID: mickeyj1
LANG: C
TASK: calfflac
*/
#include <stdio.h>
#include <assert.h>

#define MAX_INPUT 20000
#define MAX_OUTPUT 20000

int
main(int argc, char** argv) {
  char buf_input[MAX_INPUT];
  short indexes[MAX_OUTPUT];
  char buf[MAX_OUTPUT];

  int len_buf_input = 0;
  int len_buf = 0;
  char c;

  FILE* fin = fopen("calfflac.in", "r");
  assert(fin != NULL);
  while ((c = (char)fgetc(fin)) != EOF) {
    buf_input[len_buf_input] = c;
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
      if (c >= 'a') {
        c -= 'a' - 'A';
      }
      buf[len_buf] = c;
      indexes[len_buf] = len_buf_input;
      len_buf++;
    }
    len_buf_input++;
  }
  fclose(fin);

  int i;
  int max_len = 0;
  int pos_left;
  int pos_right;
  char* left;
  char* right;
  char* tmp;
  int len;
  for (i = 0; i < len_buf; i++) {
    tmp = buf + i;
    /* for the cases where buf + i is the central char of the palindrome. */
    for (
      left = tmp - 1, right = tmp + 1;
      left >= buf && right < buf + len_buf && *left == *right;
      left--, right++
    );
    left++;
    right--;
    len = right - left + 1;
    if (len > max_len) {
      max_len = len;
      pos_left = left - buf;
      pos_right = right - buf;
    }

    /* for the cases where buf is the left char of the two in the center. */
    for (
      left = tmp, right = tmp + 1;
      left >= buf && right < buf + len_buf && *left == *right;
      left--, right++
    );
    left++;
    right--;
    len = right - left + 1;
    if (len > max_len) {
      max_len = len;
      pos_left = left - buf;
      pos_right = right - buf;
    }
  }

  FILE* fout = fopen("calfflac.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", max_len);
  for (i = indexes[pos_left]; i <= indexes[pos_right]; i++) {
    fputc((int)buf_input[i], fout);
  }
  fprintf(fout, "\n");
  fclose(fout);

  return 0;
}
