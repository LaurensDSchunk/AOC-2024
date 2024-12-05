
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

vector<int> correctLine(unordered_map<int, vector<int>> &rules,
                        vector<int> &update) {

  vector<int> newUpdate(update.size());
  // in the rules, the key must come before everythig in the vector;
  for (int i = 0; i < update.size(); i++) {
    auto it = rules.find(update.at(i));
    if (it != rules.end()) {
      // Key exists
      // now see if any of the things in its array match stuff in update
      vector<int> ruleValues = rules[update.at(i)];
      int values = 0;

      for (int j = 0; j < update.size(); j++) {
        for (int k = 0; k < ruleValues.size(); k++) {
          if (update.at(j) == ruleValues.at(k)) {
            values++;
          }
        }
      }

      newUpdate.at(newUpdate.size() - values - 1) = update.at(i);
    }
  }

  return newUpdate;
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
  // int must come before everythign in vector
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
      if (!checkLine(rules, update) && update.size() != 0) {
        update = correctLine(rules, update);
        int midI = (int)update.size() / 2;
        total += update.at(midI);
      }
    }
  }
  cout << total << endl;
}
