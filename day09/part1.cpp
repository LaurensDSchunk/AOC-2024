#include "utils.h"
#include <string>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  ifstream file(argv[1]);
  if (!file) {
    cerr << "Error: Unable to open file" << endl;
    return 1;
  }

  string line;
  getline(file, line);
  vector<int> diskMap;

  bool on = true;
  int currentID = 0;

  for (int i = 0; i < line.length(); i++) {
    char c = line[i];
    int num = static_cast<int>(c) - '0';
    for (int i = 0; i < num; i++) {
      if (on) {
        diskMap.push_back(currentID);
      } else {
        diskMap.push_back(-1);
      }
    }
    if (on) {
      currentID++;
    }
    on = !on;
  }

  int nextIndex = 0;
  for (int i = diskMap.size() - 1; i >= 0; i--) {
    int num = diskMap.at(i);
    if (nextIndex >= i) {
      break;
    }
    if (num != -1) {
      while (diskMap.at(nextIndex) != -1) {
        nextIndex++;
      }

      diskMap.at(nextIndex) = num;
      diskMap.at(i) = -1;
    }
  }

  long int total;

  for (int i = 0; i < diskMap.size(); i++) {
    int num = diskMap.at(i);
    if (num != -1) {
      total += num * i;
    }
  }
  cout << total << endl;
  return 0;
}
