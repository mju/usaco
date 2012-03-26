/*
ID: mickeyj1
LANG: C
TASK: beads
*/
#include <stdio.h>
#include <assert.h>

#define MAX_N 350
#define _MAX_N ((MAX_N << 1) + 3)

int
main(int argc, char** argv) {
  FILE *fin = fopen("beads.in", "r");
  FILE *fout = fopen("beads.out", "w");

  int n;
  char beads[MAX_N + 1];
  fscanf(fin, "%d", &n);
  fscanf(fin, "%s", beads);

  /* bead_counts holds the counts for beads in the form of wxwxwxwx.
   * Elements with subscript being 0 or even numbers are for white beads.
   * Elements with odd subscripts are for either red or blue beads.
   * Bead at 2n + 1 is different from bead at 2(n + 1) + 1 in color.
   * And to make programming easier, the first three element will be appended
   * to the array, e.g. (wxw)xwxwx(wxw), (wxw)'s are the same.
   */
  int bead_counts[_MAX_N];
  int pos_bead_counts = 0;
  /* for readibility, not actually needed.  pos_bead_counts is enough. */
  int num_bead_counts;
  int pos_beads = 0;
  int i, j;
  while (beads[pos_beads] != '\0') {
    if ((pos_bead_counts & 0x1) == 0) {
      /* for even i's(or i being zero), count the white beads. */
      for (i = 0; beads[pos_beads] == 'w'; pos_beads++, i++)
        ;
      bead_counts[pos_bead_counts] = i;
    } else {
      /* for cases like xwx, the w can be considered as x. */
      for (
        i = pos_beads, j = 0;
        beads[i] == beads[pos_beads] || beads[i] == 'w';
        i++, j++
      );
      if (beads[i - 1] == 'w') {
        /* the trainling white beads should not be counted. This part can be
         * be implemented by keep track of last position for non-white bead,
         * so it does not have to do a linear search backwards.
         */
        for (i--; beads[i] != beads[pos_beads]; i--, j--)
          ;
        i++;
      }
      pos_beads = i;
      bead_counts[pos_bead_counts] = j;
    }
    pos_bead_counts++;
  }
  num_bead_counts = pos_bead_counts;

  if (num_bead_counts > 2 && beads[pos_beads - 1] == 'w') {
    /* if the last count is for white beads, merge it with the first count. */
    bead_counts[0] += bead_counts[num_bead_counts - 1];
    num_bead_counts--;
  }
  if (num_bead_counts > 5 && (((num_bead_counts - 1) >> 1) & 0x1) == 0) {
    /* the last count is for the beads of the same color as that of the first
     * count for non-white beads.  In this case, the two counts can be
     * merged.  And after the merger, the last count will be for white beads,
     * it should be merged with the first count, which is for white beads.
     */
    bead_counts[1] += bead_counts[num_bead_counts - 1];
    num_bead_counts--;
    bead_counts[0] += bead_counts[num_bead_counts - 1];
    num_bead_counts--;
  }

  /* the break point which produces the solution must be somewhere in some
   * wxwxw sequence(s).  Since the question does not ask for the position,
   * the maximum of total bead count of all wxwxw sequences serves well as the
   * solution.
   */
  int max = 0;
  if (num_bead_counts < 5) {
    for (i = 0; i < num_bead_counts; i++) {
      max += bead_counts[i];
    }
  } else {
    /* only the first three counts(wxw) need to be appended to the count array
     * to deal with the possible cycle.
     */
    bead_counts[num_bead_counts] = bead_counts[0];
    bead_counts[num_bead_counts + 1] = bead_counts[1];
    bead_counts[num_bead_counts + 2] = bead_counts[2];
    num_bead_counts += 3;

    int sum;
    for (i = 0; i <= num_bead_counts - 5; i += 2) {
      for (j = 0, sum = 0; j < 5; j++) {
        sum += bead_counts[i + j];
      }
      if (sum > max) {
        max = sum;
      }
    }
  }

  fprintf(fout, "%d\n", max);

  fclose(fin);
  fclose(fout);
  return 0;
}
