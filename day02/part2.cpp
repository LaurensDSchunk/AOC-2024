#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

bool analyzeRow(vector<int> &arr) {
  if (arr.size() < 2) {
    return true;
  }
  bool increasing = arr[0] < arr[1];
  int dampened = 0;

  for (int i = 0; i < arr.size() - 1; i++) {
    int difference = arr[i + 1] - arr[i];

    if (increasing) {
      if (difference > 3 || difference <= 0) {
        dampened++;
        if (dampened > 1) {
          return false;
        }
      }
    } else {
      if (difference < -3 || difference >= 0) {
        dampened++;
        if (dampened > 1) {
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

  int count = 0;
  string line;
  while (getline(file, line)) {
    stringstream ss(line);
    int num;
    vector<int> line;
    while (ss >> num) {
      line.push_back(num);
    }
    if (analyzeRow(line)) {
      count++;
    }
  }
  cout << count << endl;
  file.close();
}
