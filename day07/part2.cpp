#include "utils.h"
#include <sstream>
#include <string>

bool incrementOperatorArray(vector<int> &arr) {
  int n = arr.size();
  bool carry = true; // Initialize carry as true to start the increment
  for (int i = n - 1; i >= 0 && carry; i--) {
    if (arr.at(i) == 2) {
      arr.at(i) = 0; // Reset current bit to 0 and carry over
    } else {
      arr.at(i)++;   // Increment the current bit
      carry = false; // No carry needed, so stop
    }
  }

  return carry; // If carry is still true, it means the array overflowed
}

long long int evalEx(vector<int> &nums, vector<int> &ops) {
  int n = nums.size();
  long long int total = nums.at(0);
  for (int i = 1; i < n; i++) {
    if (ops.at(i - 1) == 0) {
      // Addition
      total += nums.at(i);
    } else if (ops.at(i - 1) == 1) {
      // Multiplicatoin
      total *= nums.at(i);
    } else {
      // Concatenation
      string s1 = to_string(total);
      string s2 = to_string(nums.at(i));
      string result = s1 + s2;
      total = stoll(result);
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
    vector<int> opArray(operatorCount, 0); // 0 is +, 1 is *, 2 is ||

    bool done = false;
    while (!done) {
      if (evalEx(lines.at(i).second, opArray) == target) {
        total += target;
        done = true;
      } else {
        done = incrementOperatorArray(opArray);
      }
    }
  }
  cout << total << endl;
}
