#include "utils.h"
#include <queue>
#include <unordered_set>

int countRegionSides(vector<vector<bool>> &region) {
  vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  int width = region.at(0).size();
  int height = region.size();
  int startX = -1, startY = -1;

  // get start pos of region
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (region.at(y).at(x)) {
        startX = x;
        startY = y;
        break;
      }
    }
    if (startX != -1 && startY != -1)
      break;
  }

  int sides = 0;
  int currentX = startX, currentY = startY;
  int direction = 1;
  bool first = true;

  while (first || !(currentX == startX && currentY == startY)) {
    first = false;
  }

  return sides;
}

// True if it is a side
vector<bool> getSides(vector<vector<bool>> &region, int x, int y) {
  vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  int width = region.at(0).size();
  int height = region.size();

  vector<bool> result(4, true);

  for (int i = 0; i < 4; i++) {
    auto [dy, dx] = directions.at(i);

    int newX = x + dx;
    int newY = y + dy;

    if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
      result.at(i) = !region.at(newY).at(newX);
    }
  }
  return result;
}

int getRegionPrice(vector<vector<bool>> &region) {
  vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  int width = region.at(0).size();
  int height = region.size();

  int area = 0;
  int sides = 0;

  vector<vector<vector<bool>>> borders(
      height, vector<vector<bool>>(width, vector<bool>(4, false)));

  for (int y = 0; y < region.size(); y++) {
    for (int x = 0; x < region.size(); x++) {
      if (region.at(y).at(x) == true) {
        borders.at(y).at(x) = getSides(region, x, y);
        area++;

        for (int side = 0; side < 4; side++) {
          if (borders.at(y).at(x).at(side)) {
            if (side == 1 || side == 3) {
              // Top / bottom
              if (x == 0) {
                sides++;
              } else if (!borders.at(y).at(x - 1).at(side)) {
                sides++;
              }
            } else {
              if (y == 0) {
                sides++;
              } else if (!borders.at(y - 1).at(x).at(side)) {
                sides++;
              }
            }
          }
        }
      }
    }
  }
  return sides * area;
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
