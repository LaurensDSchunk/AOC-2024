#include "utils.h"
#include <regex>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  bool enabled = true;

  ifstream file(argv[1]);
  if (!file) {
    cerr << "Error: Unable to open file" << endl;
    return 1;
  }

  regex pattern(R"((mul\((-?\d+),(-?\d+)\))|(do\(\))|(don\'t\(\)))");
  vector<pair<int, int>> results;

  smatch match;
  int total = 0;
  stringstream buffer;
  buffer << file.rdbuf(); // Read file contents into the stringstream
  string input = buffer.str();

  auto it = input.cbegin();
  while (regex_search(it, input.cend(), match, pattern)) {
    if (match[1].matched && enabled) {
      // Group 2 and Group 3 are integers for mul(x, y)
      try {
        int x = stoi(match[2]);
        int y = stoi(match[3]);
        total += x * y;
      } catch (int idc) {
      }
    } else if (match[4].matched) {
      // Matched do()
      enabled = true;
    } else if (match[5].matched) {
      // Matched don't()
      enabled = false;
    }
    it = match.suffix().first;
  }

  cout << total << endl;
  return 0;
}
