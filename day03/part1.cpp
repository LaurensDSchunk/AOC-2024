#include "utils.h"
#include <regex>

bool is_number(const std::string &s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it))
    ++it;
  return !s.empty() && it == s.end();
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

  regex pattern(R"(mul\((-?\d+),(-?\d+)\))");

  smatch match;
  int total = 0;
  stringstream buffer;
  buffer << file.rdbuf(); // Read file contents into the stringstream
  string input = buffer.str();

  auto it = input.cbegin();
  while (regex_search(it, input.cend(), match, pattern)) {
    // Extract the matched integers (x and y)
    int x = stoi(match[1].str());
    int y = stoi(match[2].str());

    total += x * y;
    it = match.suffix().first;
  }

  cout << total << endl;
  return 0;
}
