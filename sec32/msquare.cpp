/*
ID: mickeyj1
TASK: msquare
LANG: C++
*/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <assert.h>
#include <set>
#include <vector>

#define NUM_POSSIBLE_CONFS 40320/* 8 factorial. */
#define INIT_CONF 12348765
#define NUM_DIGITS 8
#define TRANSFORM_A 'A'
#define TRANSFORM_B 'B'
#define TRANSFORM_C 'C'
#define NUM_CHARS_PER_LINE 60

struct node {
  int parent;
  char transform;
  int conf;
};

int
transform_a(int conf) {
  int r;
  r = conf % 10000;
  r *= 10000;
  r += conf / 10000;
  return r;
}

int
transform_b(int conf) {
  int r;
  r = conf / 10000;
  r = (r % 10) * 1000 + r / 10;
  r *= 10000;
  conf %= 10000;
  r += (conf % 10) * 1000 + conf / 10;
  return r;
}

int
transform_c(int conf) {
  int digits[NUM_DIGITS];
  int r;

  for (int i = NUM_DIGITS - 1; i >= 0; i--) {
    digits[i] = conf % 10;
    conf /= 10;
  }

  r = digits[0];
  r *= 10;
  r += digits[5];
  r *= 10;
  r += digits[1];
  r *= 10;
  r += digits[3];
  r *= 10;
  r += digits[4];
  r *= 10;
  r += digits[6];
  r *= 10;
  r += digits[2];
  r *= 10;
  r += digits[7];

  return r;
}

int
main(int argc, char** argv, char** envp) {
  std::vector<struct node> queue;
  int pos_queue;
  std::set<int> is_visited;
  int target_conf = 0;
  int digits[NUM_DIGITS];
  struct node n;
  std::vector<char> transforms;

  std::fstream fin("msquare.in", std::ios::in);
  for (int i = 0; i < NUM_DIGITS; i++) {
    fin >> digits[i];
  }
  for (int i = 0; i < NUM_DIGITS >> 1; i++) {
    target_conf *= 10;
    target_conf += digits[i];
  }
  for (int i = NUM_DIGITS - 1; i >= NUM_DIGITS >> 1; i--) {
    target_conf *= 10;
    target_conf += digits[i];
  }
  fin.close();

  /* run BFS. */
  if (target_conf != INIT_CONF) {
    n.parent = 0;
    n.conf = INIT_CONF;
    is_visited.insert(n.conf);
    queue.push_back(n);
  }
  for (pos_queue = 0; pos_queue < queue.size(); pos_queue++) {
    n.parent = pos_queue;
    n.conf = transform_a(queue[pos_queue].conf);
    if (is_visited.count(n.conf) == 0) {
      n.transform = TRANSFORM_A;
      is_visited.insert(n.conf);
      queue.push_back(n);
      if (n.conf == target_conf) {
        break;
      }
    }
    n.conf = transform_b(queue[pos_queue].conf);
    if (is_visited.count(n.conf) == 0) {
      n.transform = TRANSFORM_B;
      is_visited.insert(n.conf);
      queue.push_back(n);
      if (n.conf == target_conf) {
        break;
      }
    }
    n.conf = transform_c(queue[pos_queue].conf);
    if (is_visited.count(n.conf) == 0) {
      n.transform = TRANSFORM_C;
      is_visited.insert(n.conf);
      queue.push_back(n);
      if (n.conf == target_conf) {
        break;
      }
    }
  }
  assert(queue.size() <= NUM_POSSIBLE_CONFS);

  /* the target is at queue.size() - 1. */
  if (pos_queue < queue.size()) {
    for (int i = queue.size() - 1; queue[i].parent != i; i = queue[i].parent) {
      transforms.push_back(queue[i].transform);
    }
  }

  std::fstream fout("msquare.out", std::ios::out);
  fout << transforms.size() << std::endl;
  if (transforms.size() > 0) {
    for (int i = 0, pos = transforms.size() - 1; pos >= 0; i++, pos--) {
      if (i > 0 && i % NUM_CHARS_PER_LINE == 0) {
        fout << std::endl;
      }
      fout << transforms[pos];
    }
  }
  fout << std::endl;
  fout.close();

  return EXIT_SUCCESS;
}
