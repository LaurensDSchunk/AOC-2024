#include "utils.h"
#include <sstream>
#include <string>
#include <utility>

const int BLINKS = 75;

void simStones(map<long long int, long int> &stoneCounts, int depth) {
  for (int i = 0; i < depth; i++) {
    map<long long int, long int> nextStoneCounts;

    for (auto &[stone, count] : stoneCounts) {
      if (stone == 0) {
        nextStoneCounts[1] += count;
      } else {
        string str = to_string(stone);
        if (str.length() % 2 == 0) {
          string s1 = str.substr(0, str.length() / 2);
          string s2 = str.substr(str.length() / 2, str.length() / 2);

          long long int left = stoll(s1);
          long long int right = stoll(s2);
          nextStoneCounts[left] += count;
          nextStoneCounts[right] += count;
        } else {
          nextStoneCounts[stone * 2024] += count;
        }
      }
    }
    stoneCounts = std::move(nextStoneCounts);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  ifstream file(argv[1]);
  if (!file) {
    cerr << "Error: Unable to open file" << endl;
    return 1;
  }

  map<long long int, long int> stoneCounts;
  string line;
  getline(file, line);
  stringstream ss(line);
  long long int num;
  while (ss >> num) {
    stoneCounts[num]++;
  }

  simStones(stoneCounts, BLINKS);

  long int total = 0;
  for (auto &[stone, count] : stoneCounts) {
    total += count;
  }

  cout << total << endl;
}
