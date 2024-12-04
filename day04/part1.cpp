#include "utils.h"
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  ifstream file(argv[1]);
  if (!file) {
    cerr << "Error: Unable to open file" << endl;
    return 1;
  }

  vector<string> puzzle;
  string line;
  while (getline(file, line)) {
    puzzle.push_back(line);
  }

  int total = 0;

  // Horizontal
  for (int y = 0; y < puzzle.size(); y++) {
    for (int x = 0; x < puzzle.at(y).length() - 3; x++) {
      string str = "";
      for (int i = 0; i < 4; i++) {
        str += puzzle.at(y)[x + i];
      }
      if (str == "XMAS" || str == "SAMX") {
        total++;
      }
    }
  }

  // Vertical
  for (int x = 0; x < puzzle.at(0).length(); x++) {
    for (int y = 0; y < puzzle.size() - 3; y++) {
      string col = "";
      for (int i = 0; i < 4; i++) {
        col += puzzle.at(y + i)[x];
      }
      if (col == "XMAS" || col == "SAMX") {
        total++;
      }
    }
  }

  // diagonal positive
  // 0 0 0 X
  // 0 0 M 0
  // 0 A 0 0
  for (int y = 0; y < puzzle.size() - 3; y++) {
    for (int x = 0; x < puzzle.at(y).length() - 3; x++) {
      string str1 = "";
      for (int i = 0; i < 4; i++) {
        str1 += puzzle.at(y + i)[x + (3 - i)];
      }
      if (str1 == "XMAS" || str1 == "SAMX") {
        total++;
      }
    }
  }

  // Diagonal negative
  //
  // X 0 0 0
  // 0 m 0 0
  // 0 0 a 0
  for (int y = 0; y < puzzle.size() - 3; y++) {
    for (int x = 0; x < puzzle.at(y).length() - 3; x++) {
      string str1 = "";
      for (int i = 0; i < 4; i++) {
        str1 += puzzle.at(y + i)[x + i];
      }
      if (str1 == "XMAS" || str1 == "SAMX") {
        total++;
      }
    }
  }

  cout << total << endl;
}
