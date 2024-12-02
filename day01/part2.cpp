

#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

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

  // value is number of key in list2
  unordered_map<int, int> count;
  for (int i = 0; i < list2.size(); i++) {
    count[list2[i]]++;
  }

  int score = 0;
  for (int i = 0; i < list1.size(); i++) {
    score += list1.at(i) * count[list1.at(i)];
  }

  cout << score << endl;

  return 0;
}
