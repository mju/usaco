/*
ID: mickeyj1
TASK: lamps
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUM_LAMPS 100
#define NUM_BUTTONS 4

/* validates the config and outputs it if valid.
 * returns one on valid input, zero otherwise.
 */
int
validate_output_config(
  char* is_pressed, int num_lamps, int num_button_presses, int* on_lamps,
  int* off_lamps, int* num_valid_configs,
  char valid_configs[][MAX_NUM_LAMPS + 1]
) {
  int num_presses = 0;
  int i;
  for (i = 0; i < NUM_BUTTONS; i++) {
    num_presses += is_pressed[i];
  }
  assert(num_presses >= 0 && num_presses <= 4);
  switch (num_presses) {
  case 0:
    if ((num_button_presses & 0x1)) {
      return 0;
    }
    break;
  case 1:
    if ((num_button_presses & 0x1) == 0 || num_button_presses < 1) {
      return 0;
    }
    break;
  case 2:
    if ((num_button_presses & 0x1) || num_button_presses < 2) {
      return 0;
    }
    break;
  case 3:
    if ((num_button_presses & 0x1) == 0 || num_button_presses < 3) {
      return 0;
    }
    break;
  case 4:
    if ((num_button_presses & 0x1) || num_button_presses < 4) {
      return 0;
    }
    break;
  }

  /* applies the effects of the buttons pressed and check if it is possible */
  char lamps[MAX_NUM_LAMPS + 1];
  memset(lamps, 1, num_lamps + 1);
  if (is_pressed[0]) {
    for (i = 1; i <= num_lamps; i++) {
      lamps[i] ^= 0x1;
    }
  }
  if (is_pressed[1]) {
    for (i = 1; i <= num_lamps; i += 2) {
      lamps[i] ^= 0x1;
    }
  }
  if (is_pressed[2]) {
    for (i = 2; i <= num_lamps; i += 2) {
      lamps[i] ^= 0x1;
    }
  }
  if (is_pressed[3]) {
    for (i = 1; i <= num_lamps; i += 3) {
      lamps[i] ^= 0x1;
    }
  }

  for (i = 0; on_lamps[i] != -1; i++) {
    if (lamps[on_lamps[i]] == 0) {
      return 0;
    }
  }
  for (i = 0; off_lamps[i] != -1; i++) {
    if (lamps[off_lamps[i]] == 1) {
      return 0;
    }
  }

  for (i = 1; i <= num_lamps; i++) {
    valid_configs[*num_valid_configs][i - 1] = '0' + lamps[i];
  }
  valid_configs[*num_valid_configs][i - 1] = '\0';
  (*num_valid_configs)++;

  return 1;
}

void
backtrack(
  int depth,
  char* is_pressed,
  int num_lamps,
  int num_button_presses,
  int* on_lamps,
  int* off_lamps,
  int* num_valid_configs,
  char valid_configs[][MAX_NUM_LAMPS + 1]
) {
  if (depth == NUM_BUTTONS) {
    validate_output_config(
      is_pressed, num_lamps, num_button_presses, on_lamps, off_lamps,
      num_valid_configs, valid_configs
    );
    return;
  }
  int i;
  for (i = 0; i <= 1; i++) {
    is_pressed[depth] = i;
    backtrack(
      depth + 1, is_pressed, num_lamps, num_button_presses, on_lamps,
      off_lamps, num_valid_configs, valid_configs
    );
  }
}

int
main(int argc, char** argv, char** envp) {
  int num_lamps;
  int num_button_presses;
  int on_lamps[MAX_NUM_LAMPS + 1];
  int off_lamps[MAX_NUM_LAMPS + 1];
  int* ptr;

  FILE* fin = fopen("lamps.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d %d", &num_lamps, &num_button_presses);
  ptr = on_lamps;
  while (1) {
    fscanf(fin, "%d", ptr);
    if (*ptr == -1) {
      break;
    }
    ptr++;
  }
  ptr = off_lamps;
  while (1) {
    fscanf(fin, "%d", ptr);
    if (*ptr == -1) {
      break;
    }
    ptr++;
  }
  fclose(fin);

  char is_pressed[NUM_BUTTONS];
  int num_valid_configs = 0;
  char valid_configs[1 << NUM_BUTTONS][MAX_NUM_LAMPS + 1];
  backtrack(
    0, is_pressed, num_lamps, num_button_presses, on_lamps, off_lamps,
    &num_valid_configs, valid_configs
  );
  qsort(
    (void*)valid_configs,
    num_valid_configs,
    sizeof(valid_configs[0]),
    (int(*)(const void*, const void*))strcmp
  );

  FILE* fout = fopen("lamps.out", "w");
  assert(fout != NULL);
  if (num_valid_configs == 0) {
    fprintf(fout, "IMPOSSIBLE\n");
  }
  int i;
  for (i = 0; i < num_valid_configs; i++) {
    fprintf(fout, "%s\n", valid_configs[i]);
  }
  fclose(fout);

  return EXIT_SUCCESS;
}
