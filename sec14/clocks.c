/*
ID: mickeyj1
LANG: C
TASK: clocks
*/
#include <stdio.h>

#define NUM_CLOCKS 9
/*
 * 10 * 3 because there is no reason for any move to be applied for more than 
 * 3 times.
 */
#define MAX_NUM_MOVES 30

#define DIAL(X) (clocks[(X)] = clocks[(X)] == 3 ? 0: clocks[(X)] + 1)
#define UNDIAL(X) (clocks[(X)] = clocks[(X)] == 0 ? 3: clocks[(X)] - 1)

void
dial(char* clocks, int move, int undo) {
  switch(move) {
    case 0:
      /* ABDE */
      if (undo) {
        UNDIAL(0);
        UNDIAL(1);
        UNDIAL(3);
        UNDIAL(4);
      } else {
        DIAL(0);
        DIAL(1);
        DIAL(3);
        DIAL(4);
      }
      break;
    case 1:
      /* ABC */
      if (undo) {
        UNDIAL(0);
        UNDIAL(1);
        UNDIAL(2);
      } else {
        DIAL(0);
        DIAL(1);
        DIAL(2);
      }
      break;
    case 2:
      /* BCEF */
      if (undo) {
        UNDIAL(1);
        UNDIAL(2);
        UNDIAL(4);
        UNDIAL(5);
      } else {
        DIAL(1);
        DIAL(2);
        DIAL(4);
        DIAL(5);
      }
      break;
    case 3:
      /* ADG */
      if (undo) {
        UNDIAL(0);
        UNDIAL(3);
        UNDIAL(6);
      } else {
        DIAL(0);
        DIAL(3);
        DIAL(6);
      }
      break;
    case 4:
      /* BDEFH */
      if (undo) {
        UNDIAL(1);
        UNDIAL(3);
        UNDIAL(4);
        UNDIAL(5);
        UNDIAL(7);
      } else {
        DIAL(1);
        DIAL(3);
        DIAL(4);
        DIAL(5);
        DIAL(7);
      }
      break;
    case 5:
      /* CFI */
      if (undo) {
        UNDIAL(2);
        UNDIAL(5);
        UNDIAL(8);
      } else {
        DIAL(2);
        DIAL(5);
        DIAL(8);
      }
      break;
    case 6:
      /* DEGH */
      if (undo) {
        UNDIAL(3);
        UNDIAL(4);
        UNDIAL(6);
        UNDIAL(7);
      } else {
        DIAL(3);
        DIAL(4);
        DIAL(6);
        DIAL(7);
      }
      break;
    case 7:
      /* GHI */
      if (undo) {
        UNDIAL(6);
        UNDIAL(7);
        UNDIAL(8);
      } else {
        DIAL(6);
        DIAL(7);
        DIAL(8);
      }
      break;
    case 8:
      /* EFHI */
      if (undo) {
        UNDIAL(4);
        UNDIAL(5);
        UNDIAL(7);
        UNDIAL(8);
      } else {
        DIAL(4);
        DIAL(5);
        DIAL(7);
        DIAL(8);
      }
      break;
  }
}

int
is_reset(char* clocks) {
  int i;
  for (i = 0; i < NUM_CLOCKS; i++) {
    if (clocks[i] != 0) {
      return 0;
    }
  }
  return 1;
}

int
dfs(
  int depth,
  int max_depth,
  int move,/* order does not matter. */
  char* clocks,
  char* moves,
  char* num_moves_done
) {
  if (depth == max_depth) {
    return is_reset(clocks);
  }
  for (; move < NUM_CLOCKS; move++) {
    if (num_moves_done[move] == 3) {
      continue;
    }
    dial(clocks, move, 0);
    moves[depth] = move;
    num_moves_done[move]++;
    if (dfs(depth + 1, max_depth, move, clocks, moves, num_moves_done)) {
      return 1;
    }
    num_moves_done[move]--;
    dial(clocks, move, 1);
  }
  return 0;
}

int
main(int argc, char** argv) {
  FILE* fin = fopen("clocks.in", "r");
  int d;
  char clocks[NUM_CLOCKS];
  int i;
  for (i = 0; i < NUM_CLOCKS; i++) {
    fscanf(fin, "%d", &d);
    clocks[i] = (d / 3) % 4;
  }
  fclose(fin);

  char moves[MAX_NUM_MOVES];
  char num_moves_done[NUM_CLOCKS];
  int depth;
  for (i = 0; i < NUM_CLOCKS; i++) {
    num_moves_done[i] = 0;
  }
  for (depth = 0; depth <= MAX_NUM_MOVES; depth++) {
    if (dfs(0, depth, 0, clocks, moves, num_moves_done)) {
      break;
    }
  }

  FILE* fout = fopen("clocks.out", "w");
  for (i = 0; i < depth; i++) {
    if (i == 0) {
      fprintf(fout, "%d", (int)(moves[i] + 1));
    } else {
      fprintf(fout, " %d", (int)(moves[i] + 1));
    }
  }
  fprintf(fout, "\n");
  fclose(fout);

  return 0;
}
