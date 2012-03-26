/*
ID: mickeyj1
LANG: C
TASK: ride
*/
#include <stdio.h>

#define N 6
#define DIVIDER 47

int
str2int(char *s) {
  int r = 1;
  int i;
  for (i = 0; s[i] != '\0'; i++) {
    r *= s[i] - (char)64;
  }
  return r;
}

int
main(int argc, char** argv) {
  FILE *fin = fopen("ride.in", "r");
  FILE *fout = fopen("ride.out", "w");
  char comet[N + 1];
  char group[N + 1];
  fscanf(fin, "%s", comet);
  fscanf(fin, "%s", group);
  if (str2int(comet) % 47 == str2int(group) % 47) {
    fprintf(fout, "%s\n", "GO");
  } else {
    fprintf(fout, "%s\n", "STAY");
  }
  fclose(fin);
  fclose(fout);
  return 0;
}
