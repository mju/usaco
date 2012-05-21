/*
ID: mickeyj1
TASK: zerosum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <stdexcept>

#define MAX_N 9
#define SPACE ' '
#define ADD '+'
#define SUB '-'
#define PRI_SPACE 1
#define PRI_ADD 0
#define PRI_SUB 0

int
get_pri_by_op(char op) {
  switch (op) {
  case SPACE:
    return PRI_SPACE;
  case ADD:
    return PRI_ADD;
  case SUB:
    return PRI_SUB;
  default:
    throw std::invalid_argument("unknown operator");
  }
}

void
get_postfix(const char* const expression, std::vector<char>& postfix) {
  std::stack<char> ops;
  for (int i = 0; expression[i] != '\0'; i++) {
    if (expression[i] >= '0' && expression[i] <= '9') {
      postfix.push_back(expression[i]);
      continue;
    }
    while (
      !ops.empty() &&
      get_pri_by_op(ops.top()) >= get_pri_by_op(expression[i])
    ) {
      postfix.push_back(ops.top());
      ops.pop();
    }
    ops.push(expression[i]);
  }
  while (!ops.empty()) {
    postfix.push_back(ops.top());
    ops.pop();
  }
}

int
evaluate_expr(const char* const expression) {
  std::vector<char> postfix;
  get_postfix(expression, postfix);
  std::stack<int> operands;
  int lhs, rhs;
  std::vector<char>::iterator biter = postfix.begin();
  const std::vector<char>::iterator eiter = postfix.end();
  for (; biter != eiter; biter++) {
    if (*biter >= '0' && *biter <= '9') {
      operands.push(*biter - '0');
      continue;
    }
    rhs = operands.top();
    operands.pop();
    lhs = operands.top();
    operands.pop();
    switch (*biter) {
    case SPACE:
      lhs = lhs * 10 + rhs;
      break;
    case ADD:
      lhs += rhs;
      break;
    case SUB:
      lhs -= rhs;
      break;
    default:
      throw std::invalid_argument("unknown operator");
    }
    operands.push(lhs);
  }
  return operands.top();
}

void
generate_expr(int depth, int n, char* expression, std::fstream& fout) {
  if (depth == n - 1) {
    if (evaluate_expr(expression) == 0) {
      fout << expression << std::endl;
    }
    return;
  }
  int idx = (depth << 1) + 1;
  expression[idx] = SPACE;
  generate_expr(depth + 1, n, expression, fout);
  expression[idx] = ADD;
  generate_expr(depth + 1, n, expression, fout);
  expression[idx] = SUB;
  generate_expr(depth + 1, n, expression, fout);
}

int
main(int argc, char** argv, char** envp) {
  int n;
  std::fstream fin, fout;
  fin.open("zerosum.in", std::ios::in);
  fin >> n;
  fin.close();
  fout.open("zerosum.out", std::ios::out);

  char expression[MAX_N << 1];
  for (int i = 0; i < (n << 1); i += 2) {
    expression[i] = '0' + (i >> 1) + 1;
    /* place holder */
    expression[i + 1] = SPACE;
  }
  expression[(n << 1) - 1] = '\0';

  generate_expr(0, n, expression, fout);

  fout.close();

  return EXIT_SUCCESS;
}
