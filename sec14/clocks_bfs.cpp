/*
ID: mickeyj1
LANG: C++
TASK: clocks
*/
/* WARNING: This version usually runs out of available memory. */
#include <fstream>
#include <list>
#include <string.h>

using namespace std;

#define DIAL(X) (children[(X)] = children[(X)] == 3 ? 0: children[(X)] + 1)

class Node {
public:
  Node(int idx, Node* node);
  Node(int idx, char* children);
  ~Node();
  void dial(int move);
  bool isReset();
  int getIdx();
  static void printPath(fstream& fout, int idx);
  static const int NUM_CLOCKS = 9;
private:
  int idx;
  char children[NUM_CLOCKS];
};

Node::Node(int idx, Node* node) {
  this->idx = idx;
  memcpy(children, node->children, NUM_CLOCKS);
}

Node::Node(int idx, char* children) {
  this->idx = idx;
  memcpy(this->children, children, NUM_CLOCKS);
}

Node::~Node() {
}

void
Node::dial(int move) {
  switch(move) {
    case 0:
      /* ABDE */
      DIAL(0);
      DIAL(1);
      DIAL(3);
      DIAL(4);
      break;
    case 1:
      /* ABC */
      DIAL(0);
      DIAL(1);
      DIAL(2);
      break;
    case 2:
      /* BCEF */
      DIAL(1);
      DIAL(2);
      DIAL(4);
      DIAL(5);
      break;
    case 3:
      /* ADG */
      DIAL(0);
      DIAL(3);
      DIAL(6);
      break;
    case 4:
      /* BDEFH */
      DIAL(1);
      DIAL(3);
      DIAL(4);
      DIAL(5);
      DIAL(7);
      break;
    case 5:
      /* CFI */
      DIAL(2);
      DIAL(5);
      DIAL(8);
      break;
    case 6:
      /* DEGH */
      DIAL(3);
      DIAL(4);
      DIAL(6);
      DIAL(7);
      break;
    case 7:
      /* GHI */
      DIAL(6);
      DIAL(7);
      DIAL(8);
      break;
    case 8:
      /* EFHI */
      DIAL(4);
      DIAL(5);
      DIAL(7);
      DIAL(8);
      break;
  }
}

bool
Node::isReset() {
  int i;
  for (i = 0; i < NUM_CLOCKS; i++) {
    if (children[i] != 0) {
      return false;
    }
  }
  return true;
}

int
Node::getIdx() {
  return idx;
}

void
Node::printPath(fstream& fout, int idx) {
  if (idx == 0) {
    return;
  }
  printPath(fout, (idx - 1) / 9);
  if (idx > 9) {
    fout << ' ';
  }
  fout << (idx - 1) % 9 + 1;
}

int
main(int argc, char** argv) {
  fstream fin;
  fin.open("clocks.in", ios::in);
  int d;
  char input[Node::NUM_CLOCKS];
  int i;
  for (i = 0; i < Node::NUM_CLOCKS; i++) {
    fin >> d;
    input[i] = (d / 3) % 4;
  }
  fin.close();

  Node* root = new Node(0, input);
  list<Node*> queue;
  queue.push_back(root);
  Node* node;
  Node* newNode;

  int idx;
  bool done = false;
  while (!done) {
    node = queue.front();
    queue.pop_front();
    for (i = 0; i < Node::NUM_CLOCKS && !done; i++) {
      newNode = new Node(9 * node->getIdx() + i + 1, node);
      newNode->dial(i);
      if (newNode->isReset()) {
        done = true;
        idx = newNode->getIdx();
      }
      queue.push_back(newNode);
    }
    delete node;
  }

  while (!queue.empty()) {
    delete queue.front();
    queue.pop_front();
  }

  fstream fout;
  fout.open("clocks.out", ios::out);
  Node::printPath(fout, idx);
  fout << endl;
  fout.close();

  return 0;
}
