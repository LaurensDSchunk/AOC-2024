/*
 *      APPROACH
 * 1. Sort each list
 * 2. Create new list of distances
 * 3. Sum up distances
 *
 */

#include <fstream>
#include <iostream>

#include <vector>

#include "utils.h"

using namespace std;

int abs(int value) {
  if (value < 0) {
    return -value;
  }
  return value;
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

  std::vector<int> list1;
  std::vector<int> list2;

  int a, b;
  while (file >> a >> b) {
    list1.push_back(a);
    list2.push_back(b);
  }

  file.close();

  utils::quicksort(list1, 0, list1.size() - 1);
  utils::quicksort(list2, 0, list2.size() - 1);

  int distance = 0;
  for (int i = 0; i < list1.size(); i++) {
    distance += abs(list1.at(i) - list2.at(i));
  }

  cout << distance << endl;

  return 0;
}
