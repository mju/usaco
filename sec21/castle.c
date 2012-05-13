/*
ID: mickeyj1
LANG: C
TASK: castle
*/
#include <stdio.h>
#include <assert.h>

#define LONGEST_SIDE 50

void
build_castle(
  int input_castle[][LONGEST_SIDE],
  short castle[][LONGEST_SIDE],
  int row,
  int col,
  int width,
  int length,
  short num_rooms,
  short* size_rooms
) {
  if (row < 0 || col < 0 || row >= length || col >= width || castle[row][col] != 0) {
    return;
  }
  castle[row][col] = num_rooms;
  size_rooms[castle[row][col]]++;
  /* west */
  if ((input_castle[row][col] & 0x1) == 0) {
    build_castle(input_castle, castle, row, col - 1, width, length, num_rooms, size_rooms);
  }
  /* north */
  if ((input_castle[row][col] & 0x2) == 0) {
    build_castle(input_castle, castle, row - 1, col, width, length, num_rooms, size_rooms);
  }
  /* east */
  if ((input_castle[row][col] & 0x4) == 0) {
    build_castle(input_castle, castle, row, col + 1, width, length, num_rooms, size_rooms);
  }
  /* south */
  if ((input_castle[row][col] & 0x8) == 0) {
    build_castle(input_castle, castle, row + 1, col, width, length, num_rooms, size_rooms);
  }
}

int
main(int argc, char** argv, char** envp) {
  int width, length;
  int input_castle[LONGEST_SIDE][LONGEST_SIDE];
  short castle[LONGEST_SIDE][LONGEST_SIDE] = {{0}};
  short size_rooms[LONGEST_SIDE * LONGEST_SIDE + 1] = {0};/* index 0 is not used */
  short num_rooms = 0;
  int i, j;

  FILE* fin = fopen("castle.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d%d", &width, &length);
  for (i = 0; i < length; i++) {
    for (j = 0; j < width; j++) {
      fscanf(fin, "%d", &input_castle[i][j]);
    }
  }
  fclose(fin);

  for (i = 0; i < length; i++) {
    for (j = 0; j < width; j++) {
      if (castle[i][j] == 0) {
        num_rooms++;
        build_castle(input_castle, castle, i, j, width, length, num_rooms, size_rooms);
      }
    }
  }

  short max_size_room = 0;
  for (i = 1; i <= num_rooms; i++) {
    if (size_rooms[i] > max_size_room) {
      max_size_room = size_rooms[i];
    }
  }

  short max_size_room_combo = 0;
  int row = -1, col = -1;
  char direction;
  int size;
  for (j = 0; j < width; j++) {
    for (i = length - 1; i >= 0; i--) {
      if (i < length - 1 && castle[i + 1][j] != castle[i][j]) {/* south */
        size = size_rooms[castle[i + 1][j]] + size_rooms[castle[i][j]];
        if (size > max_size_room_combo) {
          max_size_room_combo = size;
          col = j;
          row = i + 1;
          direction = 'N';
        }
      }
      if (j > 0 && castle[i][j - 1] != castle[i][j]) {/* west */
        size = size_rooms[castle[i][j - 1]] + size_rooms[castle[i][j]];
        if (size > max_size_room_combo) {
          max_size_room_combo = size;
          col = j - 1;
          row = i;
          direction = 'E';
        }
      }
    }
  }

  FILE* fout = fopen("castle.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%hd\n", num_rooms);
  fprintf(fout, "%hd\n", max_size_room);
  fprintf(fout, "%hd\n", max_size_room_combo);
  fprintf(fout, "%d %d %c\n", row + 1, col + 1, direction);
  fclose(fout);

  return 0;
}
