#include "utils.h"
#include <queue>
#include <vector>

/*
 * APPROACH =
 * Breadth FIRST SEARCH
 */

// Returns top right bottom left
vector<int> getNumsAround(vector<vector<int>> &map, pair<int, int> pos) {
  vector<int> result(4);
  int width = map.at(0).size();
  int height = map.size();

  // Up
  if (pos.second > 0) {
    result.at(0) = map.at(pos.second - 1).at(pos.first);
  } else {
    result.at(0) = -1;
  }

  // Right
  if (pos.first != width - 1) {
    result.at(1) = map.at(pos.second).at(pos.first + 1);
  } else {
    result.at(1) = -1;
  }

  // Down
  if (pos.second != height - 1) {
    result.at(2) = map.at(pos.second + 1).at(pos.first);
  } else {
    result.at(2) = -1;
  }

  // left
  if (pos.first > 0) {
    result.at(3) = map.at(pos.second).at(pos.first - 1);
  } else {
    result.at(3) = -1;
  }

  return result;
}

int dfs(vector<vector<int>> &map, pair<int, int> pos,
        vector<vector<bool>> &visited, int currentValue) {
  int width = map[0].size();
  int height = map.size();

  if (currentValue == 9) {
    return 1;
  }

  visited[pos.second][pos.first] = true;

  int paths = 0;
  vector<int> neighbors = getNumsAround(map, pos);

  for (int i = 0; i < 4; i++) {
    if (neighbors[i] == currentValue + 1) {
      int newX = pos.first + (i == 1) - (i == 3);  // Right (1) or Left (3)
      int newY = pos.second + (i == 2) - (i == 0); // Down (2) or Up (0)

      if (newX >= 0 && newX < width && newY >= 0 && newY < height &&
          !visited[newY][newX]) {
        paths += dfs(map, {newX, newY}, visited, currentValue + 1);
      }
    }
  }

  visited[pos.second][pos.first] = false;

  return paths;
}

int getTrails(vector<vector<int>> &map, pair<int, int> start) {
  int width = map[0].size();
  int height = map.size();

  vector<vector<bool>> visited(height, vector<bool>(width, false));

  // Start DFS from the initial position with current value as 0
  return dfs(map, start, visited, 0);
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

  vector<vector<int>> topMap;
  vector<pair<int, int>> trailHeads; // x, y
  string line;
  int currentRow = 0;
  while (getline(file, line)) {
    vector<int> row(line.length());

    for (int i = 0; i < line.length(); i++) {
      int num = line[i] - '0';
      if (num == 0) {
        trailHeads.push_back({i, currentRow});
      }
      row.at(i) = num;
    }

    topMap.push_back(row);

    currentRow++;
  }

  int total = 0;
  for (int i = 0; i < trailHeads.size(); i++) {
    total += getTrails(topMap, trailHeads.at(i));
  }

  cout << total << endl;
}
