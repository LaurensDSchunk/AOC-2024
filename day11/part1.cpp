#include "utils.h"
#include <sstream>
#include <string>

void step(vector<long long int> &stones) {
  for (int i = 0; i < stones.size(); i++) {
    string str = to_string(stones.at(i));
    if (stones.at(i) == 0) {
      stones.at(i) = 1;
    } else if (str.length() % 2 == 0) {
      string s1 = str.substr(0, str.length() / 2);
      string s2 = str.substr(str.length() / 2, str.length() / 2);
      stones.at(i) = stoll(s2);
      stones.insert(stones.begin() + i, stoll(s1));
      i++;
    } else {
      stones.at(i) *= 2024;
    }
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

  vector<long long int> stones;
  string line;
  getline(file, line);
  stringstream ss(line);
  long long int num;
  while (ss >> num) {
    stones.push_back(num);
  }

  int blinks = 25;
  for (int i = 0; i < blinks; i++) {
    step(stones);
  }

  cout << stones.size() << endl;
}
