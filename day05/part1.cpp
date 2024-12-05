#include "utils.h"
#include <cmath>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool checkLine(unordered_map<int, vector<int>> &rules, vector<int> &update) {
  for (int i = 0; i < update.size(); i++) {
    int currentInt = update.at(i);
    vector<int> cantBeBefore = rules[currentInt];
    for (int x = 0; x < i; x++) {
      for (int rule = 0; rule < cantBeBefore.size(); rule++) {
        if (update.at(x) == cantBeBefore.at(rule)) {
          return false;
        }
      }
    }
  }
  return true;
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

  bool rulesSection = true;
  unordered_map<int, vector<int>> rules;
  vector<vector<int>> updates;
  int total = 0;
  string line;
  while (getline(file, line)) {
    if (line == "") {
      rulesSection = false;
      continue;
    }
    stringstream linestream(line);
    if (rulesSection) {
      int part1;
      int part2;
      char trash;
      linestream >> part1;
      linestream >> trash;
      linestream >> part2;

      rules[part1].push_back(part2);
    } else {
      // In update section
      vector<int> update;
      int value;
      while (linestream >> value) {
        update.push_back(value);
        if (linestream.peek() == ',') {
          linestream.ignore(); // Ignore the comma
        }
      }
      if (checkLine(rules, update) && update.size() != 0) {
        int midI = (int)update.size() / 2;
        total += update.at(midI);
      }
    }
  }
  cout << total << endl;
}
