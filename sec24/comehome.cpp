/*
ID: mickeyj1
TASK: comehome
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <list>
#include <utility>
#include <assert.h>

#define SOURCE 'Z'
#define NUM_NODES 52

int
letter2idx(char letter) {
  return
    (letter >= 'A' && letter <= 'Z')?
      letter - 'A': (NUM_NODES >> 1) + letter - 'a';
}

char
idx2letter(int idx) {
  return (idx < (NUM_NODES >> 1))? (char)(idx + 'A'): (char)(idx + 'a');
}

int
main(int argc, char** argv) {
  std::vector<std::list<std::pair<int, int> > > graph(NUM_NODES);
  std::vector<bool> visited(NUM_NODES, false);
  std::vector<int> opt_dists(NUM_NODES, -1);
  int min_dist;
  int num_paths;
  char src, sink;
  int dist;

  std::fstream fin;
  fin.open("comehome.in", std::ios::in);
  fin >> num_paths;
  for (int i = 0; i < num_paths; i++) {
    fin >> src >> sink >> dist;
    graph[letter2idx(src)].push_back(
      std::pair<int, int>(letter2idx(sink), dist)
    );
    graph[letter2idx(sink)].push_back(
      std::pair<int, int>(letter2idx(src), dist)
    );
  }
  fin.close();

  /* run dijkstra.  Stop when the first Z-to-Uppercase_sink path is found. */
  int idx;
  opt_dists[letter2idx(SOURCE)] = 0;
  while (true) {
    min_dist = -1;
    for (size_t i = 0; i < visited.size(); i++) {
      if (visited[i]) {
        continue;
      }
      if (opt_dists[i] != -1 && (min_dist == -1 || opt_dists[i] < min_dist)) {
        min_dist = opt_dists[i];
        idx = i;
      }
    }
    assert(min_dist != -1);
    if (idx != letter2idx(SOURCE) && idx < (NUM_NODES >> 1)) {
      break;
    }
    visited[idx] = true;
    std::list<std::pair<int, int> >::iterator biter = graph[idx].begin();
    const std::list<std::pair<int, int> >::iterator eiter =
      graph[idx].end();
    for (; biter != eiter; biter++) {
      dist = min_dist + biter->second;
      if (opt_dists[biter->first] == -1 || dist < opt_dists[biter->first]) {
        opt_dists[biter->first] = dist;
      }
    }
  }

  std::fstream fout;
  fout.open("comehome.out", std::ios::out);
  fout << idx2letter(idx) << ' ' << min_dist << std::endl;
  fout.close();

  return EXIT_SUCCESS;
}
