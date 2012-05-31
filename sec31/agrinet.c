/*
ID: mickeyj1
TASK: agrinet
LANG: C
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define NUM_NODES 100

typedef struct {
  int v0;
  int v1;
  int weight;
} node;

int
cmp_node(const node* lhs, const node* rhs) {
  return lhs->weight - rhs->weight;
}

/* implements path-compression. */
int
find(int vertex, int* parents) {
  if (parents[vertex] != vertex) {
    parents[vertex] = find(parents[vertex], parents);
  }
  return parents[vertex];
}

/* implements union-by-rank */
void
_union(int v0, int v1, int* parents, int* ranks) {
  int _v0 = find(v0, parents);
  int _v1 = find(v1, parents);
  if (ranks[_v0] <= ranks[_v1]) {
    parents[_v0] = parents[_v1];
    if (ranks[_v0] == ranks[_v1]) {
      ranks[_v1]++;
    }
  } else {
    parents[_v1] = parents[_v0];
  }
}

int
main(int argc, char** argv, char** envp) {
  node nodes[(NUM_NODES * (NUM_NODES - 1)) >> 1];
  int pos = 0;
  int weight;
  int parents[NUM_NODES];
  int ranks[NUM_NODES] = {0};
  int num_nodes;
  int num_edges = 0;
  int total_weight = 0;
  int i, j;

  FILE* fin = fopen("agrinet.in", "r");
  assert(fin != NULL);
  fscanf(fin, "%d", &num_nodes);
  for (i = 0; i < num_nodes; i++) {
    for (j = 0; j < num_nodes; j++) {
      fscanf(fin, "%d", &weight);
      if (i < j) {
        nodes[pos].v0 = i;
        nodes[pos].v1 = j;
        nodes[pos].weight = weight;
        pos++;
      }
    }
  }
  fclose(fin);

  /* run krukal's algorithm with union-find */
  qsort(
    nodes,
    pos,
    sizeof(nodes[0]),
    (int(*)(const void*, const void*))cmp_node
  );

  for (i = 0; i < num_nodes; i++) {
    parents[i] = i;
  }

  for (i = 0; num_edges < num_nodes - 1 && i < pos; i++) {
    if (find(nodes[i].v0, parents) == find(nodes[i].v1, parents)) {
      continue;
    }
    total_weight += nodes[i].weight;
    num_edges++;
    _union(nodes[i].v0, nodes[i].v1, parents, ranks);
  }
  assert(i < pos);

  FILE* fout = fopen("agrinet.out", "w");
  assert(fout != NULL);
  fprintf(fout, "%d\n", total_weight);
  fclose(fout);

  return EXIT_SUCCESS;
}
