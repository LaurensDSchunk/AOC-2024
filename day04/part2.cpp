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

  for (int y = 0; y < puzzle.size() - 2; y++) {
    for (int x = 0; x < puzzle.at(y).length() - 2; x++) {
      // Diagonal Down
      string str1 = "";
      for (int i = 0; i < 3; i++) {
        str1 += puzzle.at(y + i)[x + i];
      }

      // Diagonal Up
      string str2 = "";
      for (int i = 0; i < 3; i++) {
        str2 += puzzle.at(y + i)[x + 2 - i];
      }
      if ((str1 == "MAS" || str1 == "SAM") &&
          (str2 == "MAS" || str2 == "SAM")) {
        total++;
      }
    }
  }

  cout << total << endl;
}
