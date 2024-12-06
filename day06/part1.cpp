#include "utils.h"
#include <string>

using namespace std;

enum Direction { UP, RIGHT, DOWN, LEFT };

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  ifstream file(argv[1]);
  if (!file) {
    cerr << "Error: Unable to open file" << endl;
    return 1;
  }

  // Step 1: construct map
  vector<vector<char>> map;
  int guardX;
  int guardY;
  Direction facing;

  string line;
  int fillY = 0;
  // Fill map and get guard pos and facing
  while (getline(file, line)) {
    vector<char> newRow(line.length());
    for (int i = 0; i < line.length(); i++) {
      char c = line[i];
      switch (c) {
      case '^':
        guardX = i;
        guardY = fillY;
        facing = UP;
        newRow.at(i) = '.';
        break;
      case '>':
        guardX = i;
        guardY = fillY;
        facing = RIGHT;
        newRow.at(i) = '.';
        break;
      case 'V':
        guardX = i;
        guardY = fillY;
        facing = DOWN;
        newRow.at(i) = '.';
        break;
      case '<':
        guardX = i;
        guardY = fillY;
        facing = LEFT;
        newRow.at(i) = '.';
        break;
      default:
        newRow.at(i) = c;
      }
    }
    map.push_back(newRow);
    fillY++;
  }

  int mapHeight = map.size();
  int mapWidth = map.at(0).size();
  vector<vector<bool>> visited(mapHeight, vector<bool>(mapWidth));
  visited.at(guardY).at(guardX) = true;
  bool inmap = true;

  while (inmap) {
    switch (facing) {
    case UP:
      if (guardY == 0) {
        inmap = false;
        break;
      }
      if (map.at(guardY - 1).at(guardX) == '#') {
        // turn
        facing = RIGHT;
      } else {
        guardY--;
      }
      visited.at(guardY).at(guardX) = true;
      break;
    case RIGHT:
      if (guardX == mapWidth - 1) {
        inmap = false;
        break;
      }
      if (map.at(guardY).at(guardX + 1) == '#') {
        // turn
        facing = DOWN;
      } else {
        guardX++;
      }
      visited.at(guardY).at(guardX) = true;
      break;
    case DOWN:
      if (guardY == mapHeight - 1) {
        inmap = false;
        break;
      }
      if (map.at(guardY + 1).at(guardX) == '#') {
        // turn
        facing = LEFT;
      } else {
        guardY++;
      }
      visited.at(guardY).at(guardX) = true;
      break;
    case LEFT:
      if (guardX == 0) {
        inmap = false;
        break;
      }
      if (map.at(guardY).at(guardX - 1) == '#') {
        // turn
        facing = UP;
      } else {
        guardX--;
      }
      visited.at(guardY).at(guardX) = true;
      break;
    }
  }

  // Count visited positions
  int total = 0;
  for (int y = 0; y < visited.size(); y++) {
    for (int x = 0; x < visited.at(0).size(); x++) {
      if (visited.at(y).at(x)) {
        total++;
      }
    }
  }

  cout << total << endl;
  return 0;
}
