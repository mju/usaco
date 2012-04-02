/*
ID: mickeyj1
LANG: C++
TASK: clocks
*/
/* WARNING: This version runs out of time. */
#include <fstream>
#include <list>
#include <string.h>

using namespace std;

#define DIAL(X) (children[(X)] = children[(X)] == 3 ? 0: children[(X)] + 1)

class Node {
public:
  Node();
  Node(char* children);
  ~Node();
  void dial(int move);
  bool isReset();
  void applyMoves(int idx);
  static void printPath(fstream& fout, int idx);
  static const int NUM_CLOCKS = 9;
private:
  char children[NUM_CLOCKS];
};

Node::Node() {
}

Node::Node(char* children) {
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

void
Node::applyMoves(int idx) {
  if (idx == 0) {
    return;
  }
  dial((idx - 1) % 9);
  applyMoves((idx - 1) / 9);
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

  Node root(input);
  Node node;
  int idx = 1;
  while (true) {
    node = root;
    node.applyMoves(idx);
    if (node.isReset()) {
      break;
    }
    idx++;
  }

  fstream fout;
  fout.open("clocks.out", ios::out);
  Node::printPath(fout, idx);
  fout << endl;
  fout.close();

  return 0;
}
