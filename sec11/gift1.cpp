/*
ID: mickeyj1
LANG: C++
TASK: gift1
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int
main(int argc, char** argv) {
  ifstream fin("gift1.in");
  ofstream fout("gift1.out");
  int np;
  fin >> np;

  vector<string> names(np);
  map<string, int> accounts;
  for (int i = 0; i < np; i++) {
    fin >> names[i];
    accounts[names[i]] = 0;
  }

  string name;
  int gift, avg_gift, num_ppl;
  for (int i = 0; i < np; i++) {
    fin >> name >> gift >> num_ppl;
    if (gift == 0 || num_ppl == 0) {
      continue;
    }
    avg_gift = gift / num_ppl;
    accounts[name] -= avg_gift * num_ppl;
    for (int j = 0; j < num_ppl; j++) {
      fin >> name;
      accounts[name] += avg_gift;
    }
  }

  vector<string>::iterator biter = names.begin();
  const vector<string>::iterator eiter = names.end();
  for (; biter != eiter; biter++) {
    fout << *biter << " " << accounts[*biter] << endl;
  }

  fin.close();
  fout.close();
  return 0;
}
