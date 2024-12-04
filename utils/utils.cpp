#include "utils.h"

using namespace std;
int partition(vector<int> &arr, int low, int high) {
  int pivot = arr.at(high); // Choose the last element as the pivot
  int i = low - 1;          // Index for smaller element

  for (int j = low; j < high; j++) {
    if (arr.at(j) < pivot) {
      // Increment i
      i++;

      // Swaps Values
      int temp = arr.at(i);
      arr.at(i) = arr.at(j);
      arr.at(j) = temp;
    }
  }

  // Place the pivot in the correct position
  int temp = arr.at(i + 1);
  arr.at(i + 1) = arr.at(high);
  arr.at(high) = temp;

  return i + 1; // Return pivot index
}

// Inplementation of Quicksort. Operates directly on input
void utils::quicksort(vector<int> &arr, int low, int high) {
  if (low < high) {
    int pivotIndex = partition(arr, low, high); // Partition the array
    quicksort(arr, low, pivotIndex - 1);        // Sort left half
    quicksort(arr, pivotIndex + 1, high);       // Sort right half
  }
}

int utils::abs(int value) {
  if (value < 0) {
    return -value;
  }
  return value;
}

string utils::fileToString(string filename) {
  string result;
  ifstream file(filename);
  string line;
  while (getline(file, line)) {
    result += line + "\n";
  }
  result.pop_back();

  return result;
}
