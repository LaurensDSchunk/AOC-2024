#include "utils.h"
#include <sstream>
#include <string>

bool incrementBitArray(vector<bool> &arr) {
  int n = arr.size();
  int carry = true;
  for (int i = n - 1; i >= 0 && carry; i--) {
    if (arr.at(i)) {
      arr.at(i) = false;
    } else {
      arr.at(i) = true;
      carry = false;
    }
  }

  return carry;
}

long long int evalEx(vector<int> &nums, vector<bool> &ops) {
  int n = nums.size();
  long long int total = nums.at(0);
  for (int i = 1; i < n; i++) {
    if (ops.at(i - 1) == false) {
      // Addition
      total += nums.at(i);
    } else {
      total *= nums.at(i);
    }
  }
  return total;
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
  vector<pair<long int, vector<int>>> lines;

  string line;
  while (getline(file, line)) {
    stringstream ss(line);
    long int firstNum;
    ss >> firstNum;
    ss.ignore();
    vector<int> nums;
    int num;
    while (ss >> num) {
      nums.push_back(num);
    }
    lines.push_back({firstNum, nums});
  }

  long long int total = 0;
  for (int i = 0; i < lines.size(); i++) {
    long int target = lines.at(i).first;

    int operatorCount = lines.at(i).second.size() - 1;
    vector<bool> opArray(operatorCount, 0); // 0 is +, 1 is *

    bool done = false;
    while (!done) {
      if (evalEx(lines.at(i).second, opArray) == target) {
        total += target;
        done = true;
      } else {
        done = incrementBitArray(opArray);
      }
    }
  }
  cout << total << endl;
}
