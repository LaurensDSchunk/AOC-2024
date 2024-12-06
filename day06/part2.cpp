#include "utils.h"
#include <string>

// UNSUCCESSFUL.  I will continue tommorow but its late now so good night

using namespace std;

enum Direction { UP, RIGHT, DOWN, LEFT };

void initMap(char *fileName, vector<vector<char>> &map, int &x, int &y,
             Direction &facing) {
  ifstream file(fileName);
  string line;
  int fillY = 0;
  // Fill map and get guard pos and facing
  while (getline(file, line)) {
    vector<char> newRow(line.length());
    for (int i = 0; i < line.length(); i++) {
      char c = line[i];
      switch (c) {
      case '^':
        x = i;
        y = fillY;
        facing = UP;
        newRow.at(i) = '.';
        break;
      case '>':
        x = i;
        y = fillY;
        facing = RIGHT;
        newRow.at(i) = '.';
        break;
      case 'V':
        x = i;
        y = fillY;
        facing = DOWN;
        newRow.at(i) = '.';
        break;
      case '<':
        x = i;
        y = fillY;
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
}

struct Position {
  int x;
  int y;
  Direction facing;
};

Position newPosExtra;

// Returns if still in the map
bool runStep(vector<vector<char>> &map, vector<vector<bool>> &visited,
             Position &pos) {
  int mapHeight = map.size();
  int mapWidth = map.at(0).size();
  Direction facing = pos.facing;
  int guardX = pos.x;
  int guardY = pos.y;

  switch (facing) {
  case UP:
    if (guardY == 0) {
      return false;
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
      return false;
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
      return false;
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
      return false;
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
  Position newPos{guardX, guardY, facing};
  newPosExtra = newPos;
  return true;
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

  vector<vector<char>> map;
  int guardX;
  int guardY;
  Direction facing;

  initMap(argv[1], map, guardX, guardY, facing);
  Position startPos{guardX, guardY, facing};

  int mapHeight = map.size();
  int mapWidth = map.at(0).size();
  vector<vector<bool>> visited(mapHeight, vector<bool>(mapWidth));
  visited.at(guardY).at(guardX) = true;

  while (runStep(map, visited, startPos)) {
  }

  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      cout << visited.at(y).at(x) << " ";
    }
    cout << endl;
  }

  int total = 0;

  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      Position loopPos = startPos;

      // Ignore existing obstacles and guard spawn
      if (map.at(y).at(x) == '#' || (y == guardY && x == guardX) ||
          visited.at(y).at(x) == false)
        continue;

      map.at(y).at(x) = '#';
      bool inMap = true;
      vector<Position> pastPositions;
      while (inMap) {
        cout << loopPos.x << " " << loopPos.y << endl;
        inMap = runStep(map, visited, loopPos);
        loopPos = newPosExtra;
        cout << loopPos.x << " " << loopPos.y << endl;

        for (int i = 0; i < pastPositions.size(); i++) {
          Position pos = pastPositions.at(i);
          if (pos.x == loopPos.x && pos.y == loopPos.y &&
              pos.facing == loopPos.facing) {
            // Loop achived
            total++;
            inMap = false;
          }
        }
        // No loop found yet
        pastPositions.push_back(loopPos);
      }

      map.at(y).at(x) = '.';
    }
  }

  cout << total << endl;
  return 0;
}
