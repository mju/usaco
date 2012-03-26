/*
ID: mickeyj1
LANG: C++
TASK: namenum
*/
#include <iostream>
#include <fstream>
#include <string>
#include <set>

#define M 8
#define N 3

void
findNames(
  int n,
  int lenNum, 
  std::string& num,
  std::string& buf,
  char keypad[][N],
  std::set<std::string>& dict,
  std::fstream& fout,
  bool& atLeastOne
) {
  if (n == lenNum) {
    if (dict.count(buf) == 1) {
      atLeastOne = true;
      fout << buf << std::endl;
    }
    return;
  }

  for (int i = 0; i < N; i++) {
    buf[n] = keypad[num[n] - '0' - 2][i];
    findNames(n + 1, lenNum, num, buf, keypad, dict, fout, atLeastOne);
  }
}

int
main(int argc, char** argv) {
  std::fstream fin;
  fin.open("namenum.in", std::ios::in);
  std::fstream fdict;
  fdict.open("dict.txt", std::ios::in);

  std::string num;
  fin >> num;
  fin.close();

  std::set<std::string> dict;
  std::string name;
  while (fdict >> name) {
    dict.insert(name);
  }
  fdict.close();

  char keypad[M][N] = {
    {'A', 'B', 'C'},
    {'D', 'E', 'F'},
    {'G', 'H', 'I'},
    {'J', 'K', 'L'},
    {'M', 'N', 'O'},
    {'P', 'R', 'S'},
    {'T', 'U', 'V'},
    {'W', 'X', 'Y'}
  };

  std::fstream fout;
  fout.open("namenum.out", std::ios::out);

  int lenNum = num.length();
  bool none = false;
  for (int i = 0; i < lenNum; i++) {
    if (num[i] == '0' || num[i] == '1') {
      none = true;
      fout << "NONE" << std::endl;
      break;
    }
  }

  if (!none) {
    std::string buf(num);
    bool atLeastOne = false;
    findNames(0, lenNum, num, buf, keypad, dict, fout, atLeastOne);
    if (!atLeastOne) {
      fout << "NONE" << std::endl;
    }
  }

  fout.close();
  return 0;
}
