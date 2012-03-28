/*
TASK: packrec
ID: mickeyj1
LANG: C
*/
#include <stdio.h>
#include <assert.h>

#define NUM_RECS 4
#define MAX_SIDE 200

struct rectangle {
  int height;
  int width;
};

/*
 * check the following configuration.
 * *** *** *** ***
 * * * * * * * * *
 * * * * * * * * *
 * *** *** *** ***
 */
void
check0(struct rectangle* recs, int* output, int* min_area) {
  int i;
  int max_height = recs[0].height;
  int width = recs[0].width;
  for (i = 1; i < NUM_RECS; i++) {
    if (recs[i].height > max_height) {
      max_height = recs[i].height;
    }
    width += recs[i].width;
  }

  int area = max_height * width;
  if (area <= *min_area) {
    *min_area = area;
    if (max_height > width) {
      output[width] = max_height;
    } else {
      output[max_height] = width;
    }
  }
}

/*
 * check the following configuration.
 * *** *** ***
 * * * * * * *
 * * * * * * *
 * *** *** ***
 * ***********
 * *         *
 * ***********
 */
void
check1(struct rectangle* recs, int* output, int* min_area) {
  int height;
  int max_height;
  int max_width;
  int width;
  int area;
  int i, j;
  for (i = 0; i < NUM_RECS; i++) {
    height = recs[i].height;
    max_width = recs[i].width;
    max_height = 0;
    width = 0;
    for (j = 0; j < NUM_RECS; j++) {
      if (j != i) {
        if (recs[j].height > max_height) {
          max_height = recs[j].height;
        }
        width += recs[j].width;
      }
    }
    if (width > max_width) {
      max_width = width;
    }
    height += max_height;
    area = height * max_width;
    if (area <= *min_area) {
      *min_area = area;
      if (height > max_width) {
        output[max_width] = height;
      } else {
        output[height] = max_width;
      }
    }
  }
}

/*
 * check the following configuration.
 * *** *** ***
 * *3* *2* *0*
 * * * * * * *
 * *** *** * *
 * ******* * *
 * *1    * * *
 * ******* ***
 */
void
check2(struct rectangle* recs, int* output, int* min_area) {
  int i, j, k;
  int rec0, rec1, rec2, rec3;
  int height;
  int width;
  int area;
  for (i = 0; i < NUM_RECS; i++) {
    rec0 = i;
    for (j = 0; j < NUM_RECS; j++) {
      if (j == rec0) {
        continue;
      }
      rec1 = j;
      rec2 = -1;
      for (k = 0; k < NUM_RECS; k++) {
        if (k != rec0 && k != rec1) {
          if (rec2 == -1) {
            rec2 = k;
          } else {
            rec3 = k;
          }
        }
      }

      width = recs[rec0].width;
      int tmp_w = recs[rec2].width + recs[rec3].width;
      if (tmp_w > recs[rec1].width) {
        width += tmp_w;
      } else {
        width += recs[rec1].width;
      }

      int tmp_h = recs[rec1].height;
      if (recs[rec2].height > recs[rec3].height) {
        tmp_h += recs[rec2].height;
      } else {
        tmp_h += recs[rec3].height;
      }
      if (tmp_h > recs[rec0].height) {
        height = tmp_h;
      } else {
        height = recs[rec0].height;
      }
      area = height * width;
      if (area <= *min_area) {
        *min_area = area;
        if (height < width) {
          output[height] = width;
        } else {
          output[width] = height;
        }
      }
    }
  }
}

/*
 * check the following configurations.
 * *** *** ***     *** *** ***
 * * * * * * *     *2* *1* *0*
 * * * * * * *     * * * * * *
 * * * *** * *     *** * * * *
 * * * *** * * and *** * * * *
 * * * * * * *     *3* * * * *
 * * * * * * *     * * * * * *
 * *** *** ***     *** *** ***
 */
void
check3(struct rectangle* recs, int* output, int* min_area) {
  int i, j, k;
  int width;
  int height;
  int area;
  int rec0, rec1, rec2, rec3;
  for (i = 0; i < NUM_RECS - 1; i++) {
    rec0 = i;
    for (j = i + 1; j < NUM_RECS; j++) {
      rec1 = j;
      rec2 = -1;
      for (k = 0; k < NUM_RECS; k++) {
        if (k != rec0 && k != rec1) {
          if (rec2 == -1) {
            rec2 = k;
          } else {
            rec3 = k;
          }
        }
      }

      width = recs[rec0].width + recs[rec1].width;
      if (recs[rec2].width > recs[rec3].width) {
        width += recs[rec2].width;
      } else {
        width += recs[rec3].width;
      }

      height = recs[rec2].height + recs[rec3].height;
      if (recs[rec1].height > height) {
        height = recs[rec1].height;
      }
      if (recs[rec0].height > height) {
        height = recs[rec0].height;
      }

      area = height * width;
      if (area <= *min_area) {
        *min_area = area;
        if (height < width) {
          output[height] = width;
        } else {
          output[width] = height;
        }
      }
    }
  }
}

void
_check4(
  struct rectangle* recs,
  int* output,
  int* min_area,
  int rec0,
  int rec1,
  int rec2,
  int rec3
) {
  int tmp_h = recs[rec0].height + recs[rec1].height;
  int height = recs[rec2].height + recs[rec3].height;
  if (tmp_h > height) {
    height = tmp_h;
  }

  int width = recs[rec0].width + recs[rec2].width;
  int tmp_w = recs[rec1].width + recs[rec3].width;
  if (tmp_w > width) {
    width = tmp_w;
  }
  if (recs[rec1].height > recs[rec3].height) {
    tmp_w = recs[rec1].width + recs[rec2].width;
    if (tmp_w > width) {
      width = tmp_w;
    }
  } else if (recs[rec1].height < recs[rec3].height) {
    tmp_w = recs[rec0].width + recs[rec3].width;
    if (tmp_w > width) {
      width = tmp_w;
    }
  }

  int area = height * width;
  if (area <= *min_area) {
    *min_area = area;
    if (height < width) {
      output[height] = width;
    } else {
      output[width] = height;
    }
  }
}

/*
 * check the following configuration.
 * *** **********
 * *0* *      2 *
 * * * **********
 * * *        ***
 * * *        *3*
 * ***        * *
 * ********** * *
 * *1       * * *
 * ********** ***
 */
void
check4(struct rectangle* recs, int* output, int* min_area) {
  _check4(recs, output, min_area, 0, 1, 2, 3);
  _check4(recs, output, min_area, 1, 0, 2, 3);
  _check4(recs, output, min_area, 0, 2, 1, 3);
  _check4(recs, output, min_area, 2, 0, 1, 3);
  _check4(recs, output, min_area, 0, 3, 1, 2);
  _check4(recs, output, min_area, 3, 0, 1, 2);
}

void
pack(int depth, struct rectangle* recs, int* output, int* min_area) {
  if (depth == NUM_RECS) {
    check0(recs, output, min_area);
    check1(recs, output, min_area);
    check2(recs, output, min_area);
    check3(recs, output, min_area);
    check4(recs, output, min_area);
    return;
  }

  pack(depth + 1, recs, output, min_area);

  int tmp = recs[depth].height;
  recs[depth].height = recs[depth].width;
  recs[depth].width = tmp;

  pack(depth + 1, recs, output, min_area);

  tmp = recs[depth].height;
  recs[depth].height = recs[depth].width;
  recs[depth].width = tmp;
}

int
main(int argc, char** argv) {
  struct rectangle recs[NUM_RECS];
  int output[MAX_SIDE] = {0};
  int min_area = MAX_SIDE * MAX_SIDE;
  int i;

  FILE* fin = fopen("packrec.in", "r");
  assert(fin != NULL);
  for (i = 0; i < NUM_RECS; i++) {
    fscanf(fin, "%d %d", &recs[i].height, &recs[i].width);
  }
  fclose(fin);

  pack(0, recs, output, &min_area);

  FILE* fout = fopen("packrec.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", min_area);
  for (i = 0; i < MAX_SIDE; i++) {
    if (output[i] != 0 && i * output[i] == min_area) {
      fprintf(fout, "%d %d\n", i, output[i]);
    }
  }
  fclose(fout);

  return 0;
}
