/*
ID: mickeyj1
TASK: cowtour
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NUM_NODES 150
#define NA -1.0
#define BOUND -0.05
#define IS_NOT_NA(x) ((x) > BOUND)

typedef struct {
  int x;
  int y;
} point;

double
get_dist(point* p0, point* p1) {
  double diffx = p0->x - p1->x;
  double diffy = p0->y - p1->y;
  return sqrt(diffx * diffx + diffy * diffy);
}

void
floyd_warshall(double graph[][MAX_NUM_NODES], int num_nodes) {
  int i, j, k;
  for (i = 0; i < num_nodes; i++) {
    for (j = 0; j < num_nodes; j++) {
      for (k = 0; k < num_nodes; k++) {
        if (IS_NOT_NA(graph[j][i]) && IS_NOT_NA(graph[i][k])) {
          double dist = graph[j][i] + graph[i][k];
          if (!IS_NOT_NA(graph[j][k]) || dist < graph[j][k]) {
            graph[j][k] = dist;
          }
        }
      }
    }
  }
}

int
main(int argc, char** argv, char** envp) {
  int num_nodes;
  point points[MAX_NUM_NODES];
  char is_connected[MAX_NUM_NODES][MAX_NUM_NODES];
  int num_parts = 1;
  short nodes_parts[MAX_NUM_NODES] = {0};
  double diameters[MAX_NUM_NODES + 1];
  double graph[MAX_NUM_NODES][MAX_NUM_NODES];
  double max_dists[MAX_NUM_NODES];
  double min_diameter = NA;
  int i, j, k, l;

  FILE* fin = fopen("cowtour.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d", &num_nodes);
  for (i = 0; i < num_nodes; i++) {
    fscanf(fin, "%d%d", &points[i].x, &points[i].y);
  }
  getc(fin);/* to remove the trailing newline character. */
  for (i = 0; i < num_nodes; i++) {
    for (j = 0; j < num_nodes; j++) {
      is_connected[i][j] = getc(fin) - '0';
    }
    getc(fin);/* to remove the trailing newline characters. */
  }
  fclose(fin);

  /* find the partitions. */
  while (1) {
    for (i = 0; i < num_nodes && nodes_parts[i] != 0; i++);
    if (i == num_nodes) {
      num_parts--;
      break;
    }
    nodes_parts[i] = -1;
    while (1) {
      for (i = 0; i < num_nodes && nodes_parts[i] != -1; i++);
      if (i == num_nodes) {
        break;
      }
      nodes_parts[i] = num_parts;
      for (j = 0; j < num_nodes; j++) {
        if (nodes_parts[j] == 0 && is_connected[i][j]) {
          nodes_parts[j] = -1;
        }
      }
    }
    num_parts++;
  }

  /* do floyd-warshall. */
  for (i = 0; i < num_nodes; i++) {
    for (j = i; j < num_nodes; j++) {
      if (i == j) {
        graph[i][j] = 0.0;
        continue;
      }
      if (is_connected[i][j]) {
        graph[i][j] = graph[j][i] = get_dist(points + i, points + j);
      } else {
        graph[i][j] = graph[j][i]  = NA;
      }
    }
  }
  floyd_warshall(graph, num_nodes);

  /* try out different connections between the two partitions. */
  for (i = 0; i < num_nodes; i++) {
    max_dists[i] = 0.0;
    for (j = 0; j < num_nodes; j++) {
      if (IS_NOT_NA(graph[i][j]) && graph[i][j] > max_dists[i]) {
        max_dists[i] = graph[i][j];
      }
    }
  }
  for (i = 1; i <= num_parts; i++) {
    diameters[i] = 0.0;
    for (j = 0; j < num_nodes; j++) {
      if (nodes_parts[j] != i) {
        continue;
      }
      if (max_dists[j] > diameters[i]) {
        diameters[i] = max_dists[j];
      }
    }
  }
  for (i = 1; i < num_parts; i++) {
    for (j = i + 1; j <= num_parts; j++) {
      for (k = 0; k < num_nodes; k++) {
        if (nodes_parts[k] != i) {
          continue;
        }
        for (l = 0; l < num_nodes; l++) {
          if (nodes_parts[l] != j) {
            continue;
          }
          double dist =
            get_dist(points + k, points + l) + max_dists[k] + max_dists[l];
          if (diameters[nodes_parts[k]] > dist) {
            dist = diameters[nodes_parts[k]];
          }
          if (diameters[nodes_parts[l]] > dist) {
            dist = diameters[nodes_parts[l]];
          }
          if (!IS_NOT_NA(min_diameter) || dist < min_diameter) {
            min_diameter = dist;
          }
        }
      }
    }
  }

  FILE* fout = fopen("cowtour.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%.6lf\n", min_diameter);
  fclose(fout);

  return EXIT_SUCCESS;
}
