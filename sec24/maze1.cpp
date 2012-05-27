/*
ID: mickeyj1
TASK: maze1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <utility>
#include <assert.h>

#define MAX_WIDTH 38
#define MAX_HEIGHT 100

using namespace std;

int
main(int argc, char** argv, char** envp) {
  int exits[2];
  int num_exits = 0;
  vector<vector<int> > maze;
  int max_min = -1;
  int width, height;
  string line;

  fstream fin("maze1.in", ios::in);
  fin >> width >> height;
  /* get rid of the \n */
  getline(fin, line);
  maze.resize(width * height);
  for (int i = 0; i < (height << 1) + 1; i++) {
    getline(fin, line);
    for (int j = 0; j < line.size(); j++) {
      if (
        (j == 0 || j == (width << 1) || i == 0 || i == (height << 1)) &&
        line[j] == ' '
      ) {
        if (j == 0) {
          exits[num_exits++] = (i >> 1) * width;
        } else if (j == (width << 1)) {
          exits[num_exits++] = ((i >> 1) + 1) * width - 1;
        } else if (i == 0) {
          exits[num_exits++] = (j >> 1);
        } else if (i == (height << 1)) {
          exits[num_exits++] = ((height - 1) * width) + (j >> 1);
        }
        continue;
      }

      if ((i & 0x1) == 0) {
        if ((j & 0x1) == 0) {
          continue;
        }
        if (line[j] == '-') {
          continue;
        }
        int room_up = ((i - 1) >> 1) * width + (j >> 1);
        int room_down = ((i + 1) >> 1) * width + (j >> 1);
        maze[room_up].push_back(room_down);
        maze[room_down].push_back(room_up);
      } else {
        if (j & 0x1) {
          continue;
        }
        if (line[j] == '|') {
          continue;
        }
        int room_left = (i >> 1) * width + ((j - 1) >> 1);
        int room_right = (i >> 1) * width + ((j + 1) >> 1);
        maze[room_left].push_back(room_right);
        maze[room_right].push_back(room_left);
      }
    }
  }
  fin.close();
  assert(num_exits == 2);

  /* debugging output
  for (int i = 0; i < height * width; i++) {
    cout << i << ":";
    list<int>::iterator biter = maze[i].begin();
    const list<int>::iterator eiter = maze[i].end();
    for (; biter != eiter; biter++) {
      cout << ' ' << *biter;
    }
    cout << endl;
  }
  cout << "exit 0: " << exits[0] << endl;
  cout << "exit 1: " << exits[1] << endl;
  */

  /* run BFS for each node */
  for (int node = 0; node < width * height; node++) {
    int len_path = -1;
    vector<pair<int, int> > bfs_queue;
    vector<bool> visited(width * height, false);
    int head = 0;
    bfs_queue.push_back(pair<int, int>(node, 1));
    visited[node] = true;
    if (node == exits[0] || node == exits[1]) {
      len_path = 1;
    }
    while (len_path == -1) {
      vector<int>::iterator biter = maze[bfs_queue[head].first].begin();
      const vector<int>::iterator eiter = maze[bfs_queue[head].first].end();
      for (; biter != eiter; biter++) {
        if (visited[*biter]) {
          continue;
        }
        visited[*biter] = true;
        if (*biter == exits[0] || *biter == exits[1]) {
          len_path = bfs_queue[head].second + 1;
          break;
        }
        bfs_queue.push_back(pair<int, int>(*biter, bfs_queue[head].second + 1));
      }
      head++;
    }
    if (max_min == -1 || len_path > max_min) {
      max_min = len_path;
    }
  }

  fstream fout("maze1.out", ios::out);
  fout << max_min << endl;
  fout.close();

  return EXIT_SUCCESS;
}
