#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

namespace utils {
void quicksort(vector<int> &arr, int low, int high);
int abs(int value);
string fileToString(string filename);
} // namespace utils

#endif // UTILS_H
