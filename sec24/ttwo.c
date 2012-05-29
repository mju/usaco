/*
ID: mickeyj1
TASK: ttwo
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define DIM 10
#define NUM_DIRECTIONS 4
#define OBSTACLE '*'
#define EMPTY '.'
#define COWS 'C'
#define FARMER 'F'

enum DIR {
  NORTH,
  EAST,
  SOUTH,
  WEST,
  NUM_DIRS
};

typedef struct {
  int row;
  int col;
  int dir;
} position;

void
move(char map[][DIM + 2 + 1], position* pos) {
  position next_step = *pos;
  if (pos->dir == NORTH) {
    next_step.row--;
  } else if (pos->dir == EAST) {
    next_step.col++;
  } else if (pos->dir == SOUTH) {
    next_step.row++;
  } else if (pos->dir == WEST) {
    next_step.col--;
  }

  if (map[next_step.row][next_step.col] == OBSTACLE) {
    pos->dir++;
    if (pos->dir == NUM_DIRS) {
      pos->dir -= NUM_DIRS;
    }
  } else {
    pos->row = next_step.row;
    pos->col = next_step.col;
  }
}

void
chase(
  char map[][DIM + 2 + 1],
  position* pos_farmer,
  position* pos_cows,
  int* num_minutes,
  char visited[][DIM][NUM_DIRS][DIM][DIM][NUM_DIRS]
) {
  if (pos_farmer->row == pos_cows->row && pos_farmer->col == pos_cows->col) {
    return;
  }
  if (visited[
    pos_farmer->row - 1][
    pos_farmer->col - 1][
    pos_farmer->dir][
    pos_cows->row - 1][
    pos_cows->col - 1][
    pos_cows->dir
  ]) {
    *num_minutes = 0;
    return;
  }

  visited[
    pos_farmer->row - 1][
    pos_farmer->col - 1][
    pos_farmer->dir][
    pos_cows->row - 1][
    pos_cows->col - 1][
    pos_cows->dir
  ] = 1;
  (*num_minutes)++;

  /* the farmer moves */
  move(map, pos_farmer);
  /* the cows move */
  move(map, pos_cows);

  chase(map, pos_farmer, pos_cows, num_minutes, visited);
}

int
main(int argc, char** argv, char** envp) {
  position pos_cows, pos_farmer;
  int num_minutes = 0;
  char map[DIM + 2][DIM + 2 + 1];
  /* indexes are for the farmer's position and direction, and the cows'
   * position and direction.
   */
  char visited[DIM][DIM][NUM_DIRS][DIM][DIM][NUM_DIRS] =
    {{{{{{0}}}}}};
  int i, j;

  FILE* fin = fopen("ttwo.in", "r");
  assert(fin != NULL);
  for (i = 1; i <= DIM; i++) {
    fscanf(fin, "%s", map[i] + 1);
  }
  fclose(fin);

  /* set up the border facilitating coding. */
  for (i = 0; i < DIM + 2; i++) {
    map[0][i] = '*';
    map[DIM + 2 - 1][i] = OBSTACLE;
    map[i][0] = '*';
    map[i][DIM + 2 - 1] = OBSTACLE;
  }

  for (i = 1; i <= DIM; i++) {
    for (j = 1; j <= DIM; j++) {
      if (map[i][j] == FARMER) {
        pos_farmer.row = i;
        pos_farmer.col = j;
      } else if (map[i][j] == COWS) {
        pos_cows.row = i;
        pos_cows.col = j;
      }
    }
  }
  pos_farmer.dir = NORTH;
  pos_cows.dir = NORTH;

  chase(
    map,
    &pos_farmer,
    &pos_cows,
    &num_minutes,
    visited
  );

  FILE* fout = fopen("ttwo.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", num_minutes);
  fclose(fout);

  return EXIT_SUCCESS;
}
