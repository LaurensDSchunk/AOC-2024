#include "utils.h"
#include <_stdio.h>
#include <cstddef>
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
  vector<pair<int, int>> dMap; // file size, id

  bool on = true;
  int currentID = 0;

  for (int i = 0; i < line.length(); i++) {
    char c = line[i];
    int num = static_cast<int>(c) - '0';
    for (int j = 0; j < num; j++) {
      if (on) {
        diskMap.push_back(currentID);
      } else {
        diskMap.push_back(-1);
      }
    }
    if (on) {
      dMap.push_back({num, currentID});
      currentID++;
    } else {
      dMap.push_back({num, -1});
    }
    on = !on;
  }

  for (int i = dMap.size() - 1; i >= 0; i--) {
    pair<int, int> p1 = dMap.at(i);
    if (p1.second == -1) {
      // dMap.erase(dMap.begin() + i);
    } else {
      for (int j = 0; j < dMap.size(); j++) {
        if (j > i)
          break;
        pair<int, int> p2 = dMap.at(j);
        if (p2.second == -1 && p2.first >= p1.first) {
          int newLength = p2.first - p1.first;
          if (newLength == 0) {
            dMap.at(j).second = dMap.at(i).second;
            dMap.at(i).second = -1;

          } else {
            dMap.at(j).first = newLength;
            dMap.insert(dMap.begin() + j, p1);
            dMap.at(i + 1).second = -1;
          }

          break;
        }
      }
    }

    /*
    cout << "----" << endl;
    for (int a = 0; a < dMap.size(); a++) {
      int num = dMap.at(a).first;
      for (int b = 0; b < num; b++) {
        if (dMap.at(a).second == -1) {
          cout << ".";
        } else {
          cout << dMap.at(a).second;
        }
      }
    }
    cout << endl;

    string c;
    cin >> c;
    */
  }

  long int total;
  int currentIndex = 0;
  for (int i = 0; i < dMap.size(); i++) {
    int len = dMap.at(i).first;
    for (int j = 0; j < len; j++) {
      if (dMap.at(i).second != -1) {
        total += dMap.at(i).second * currentIndex;
      }
      currentIndex++;
    }
  }
  cout << total << endl;
  return 0;
}
