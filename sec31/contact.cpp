/*
ID: mickeyj1
TASK: contact
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#define NUM_PATTERNS_LINE 6

struct Pattern {
  Pattern() {
  }

  Pattern(const std::string& p, const int c): pattern(p), count(c) {
  }

  bool operator()(const Pattern& lhs, const Pattern& rhs) const {
    if (lhs.count > rhs.count) {
      return true;
    }
    if (lhs.count == rhs.count && lhs.pattern.length() < rhs.pattern.length()) {
      return true;
    }
    if (lhs.count == rhs.count && lhs.pattern.length() > rhs.pattern.length()) {
      return false;
    }
    if (lhs.count == rhs.count && lhs.pattern < rhs.pattern) {
      return true;
    }
    return false;
  }

  std::string pattern;
  int count;
};

int
main(int argc, char** argv, char** envp) {
  int min_len, max_len, num_freqs;
  std::string tmp;
  std::string seq;
  std::map<std::string, int> counter;
  std::vector<Pattern> patterns;

  std::fstream fin("contact.in", std::ios::in);
  fin >>  min_len >> max_len >> num_freqs;
  while (fin >> tmp) {
    seq.append(tmp);
  }
  fin.close();

  for (int i = 0; i < seq.size(); i++) {
    tmp.clear();
    for (int j = i; j - i < max_len && j < seq.size(); j++) {
      tmp.push_back(seq[j]);
      if (j - i + 1 < min_len) {
        continue;
      }
      if (counter.count(tmp) == 0) {
        counter[tmp] = 1;
      } else {
        counter[tmp]++;
      }
    }
  }

  std::map<std::string, int>::iterator biter = counter.begin();
  const std::map<std::string, int>::iterator eiter = counter.end();
  for (; biter != eiter; biter++) {
    patterns.push_back(Pattern(biter->first, biter->second));
  }

  std::sort(patterns.begin(), patterns.end(), Pattern());

  std::fstream fout("contact.out", std::ios::out);
  int count;
  int freq;
  int _num_freqs = 0;
  for (int i = 0 ; i < patterns.size(); i++) {
    if (i == 0 || patterns[i].count != freq) {
      _num_freqs++;
      if (_num_freqs > num_freqs) {
        break;
      }
      freq = patterns[i].count;
      count = 0;
      if (i > 0) {
        fout << std::endl;
      }
      fout << freq;
    } else {
      count++;
    }
    if (count % NUM_PATTERNS_LINE == 0) {
      fout << std::endl << patterns[i].pattern;
    } else {
      fout << ' ' << patterns[i].pattern;
    }
  }
  fout << std::endl;
  fout.close();

  return EXIT_SUCCESS;
}
