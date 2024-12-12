#include "utils.h"
#include <queue>
#include <unordered_set>

int getMatchingNeighbors(vector<vector<bool>> &garden, int x, int y) {
  int width = garden.at(0).size();
  int height = garden.size();

  int count = 0;
  bool current = true;

  if (x != 0 && garden.at(y).at(x - 1) == current)
    count++;
  if (x != width - 1 && garden.at(y).at(x + 1) == current)
    count++;
  if (y != 0 && garden.at(y - 1).at(x) == current)
    count++;
  if (y != height - 1 && garden.at(y + 1).at(x) == current)
    count++;

  return count;
}

int getRegionPrice(vector<vector<bool>> &region) {
  int area = 0;
  int perimeter = 0;

  for (int y = 0; y < region.size(); y++) {
    for (int x = 0; x < region.size(); x++) {
      if (region.at(y).at(x) == true) {
        area++;
        perimeter += 4 - getMatchingNeighbors(region, x, y);
      }
    }
  }

  return area * perimeter;
}

void updateRegionVisit(vector<vector<bool>> &fill, vector<vector<char>> &garden,
                       int x, int y) {
  int width = garden.at(0).size();
  int height = garden.size();
  char c = garden.at(y).at(x);

  queue<pair<int, int>> q;
  vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  q.push({x, y});
  fill.at(y).at(x) = true;

  while (!q.empty()) {
    auto [currX, currY] = q.front();
    q.pop();

    for (auto [dx, dy] : directions) {
      int newX = currX + dx;
      int newY = currY + dy;

      if (newX >= 0 && newX < width && newY >= 0 && newY < height &&
          fill.at(newY).at(newX) == false && garden.at(newY).at(newX) == c) {
        fill.at(newY).at(newX) = true;
        q.push({newX, newY});
      }
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

  vector<vector<char>> garden;
  unordered_set<char> plants;

  string line;
  while (getline(file, line)) {
    vector<char> row(line.length());
    for (int i = 0; i < line.length(); i++) {
      row.at(i) = line[i];
      plants.insert(line[i]);
    }
    garden.push_back(row);
  }

  int total = 0;
  vector<vector<bool>> checked(garden.size(),
                               vector<bool>(garden.at(0).size(), false));

  for (int y = 0; y < garden.size(); y++) {
    for (int x = 0; x < garden.size(); x++) {
      if (checked.at(y).at(x) == false) {
        vector<vector<bool>> region(garden.size(),
                                    vector<bool>(garden.at(0).size(), false));
        updateRegionVisit(region, garden, x, y);
        updateRegionVisit(checked, garden, x, y);
        total += getRegionPrice(region);
      }
    }
  }

  cout << total << endl;

  return 0;
}
