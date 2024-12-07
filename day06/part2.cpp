#include "utils.h"
#include <string>
#include <vector>

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

  // Define equality operator
  bool operator==(const Position &other) const {
    return x == other.x && y == other.y && facing == other.facing;
  }
};

// Define a custom hash function for Position
struct PositionHash {
  std::size_t operator()(const Position &pos) const {
    // Combine the hash of x, y, and facing
    std::size_t h1 = std::hash<int>()(pos.x);
    std::size_t h2 = std::hash<int>()(pos.y);
    std::size_t h3 = std::hash<int>()(static_cast<int>(pos.facing));
    return h1 ^ (h2 << 1) ^ (h3 << 2); // Combine hashes with bit shifts
  }
};

Position newPosExtra;

// Returns if still in the map
bool runStep(vector<vector<char>> &map, Position &pos) {
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
    break;
  }
  Position newPos{guardX, guardY, facing};
  pos = newPos;
  return true;
}

void fillVisited(vector<vector<char>> &map, vector<vector<bool>> &visited,
                 Position startPos) {
  while (runStep(map, startPos)) {
    visited.at(startPos.y).at(startPos.x) = true;
  }
}

bool detectLoop(vector<vector<char>> &map, Position startPos) {
  unordered_map<Position, int, PositionHash> pastPositions;
  pastPositions[startPos]++;

  while (runStep(map, startPos)) {
    if (pastPositions.find(startPos) != pastPositions.end()) {
      return true;
    }
    pastPositions[startPos]++;
  }

  return false;
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
  Position currentPos = startPos;

  int mapHeight = map.size();
  int mapWidth = map.at(0).size();

  vector<vector<bool>> visited(mapHeight, vector<bool>(mapWidth));
  fillVisited(map, visited, startPos);

  int total = 0;

  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      // Has to be visited, cannot be an obstacle, and cannot equal the start
      // position
      if (visited.at(y).at(x) == true &&
          !(y == startPos.y && x == startPos.x)) {
        map.at(y).at(x) = '#';

        if (detectLoop(map, startPos)) {
          total++;
        }

        map.at(y).at(x) = '.';
      }
    }
  }
  cout << total << endl;

  return 0;
}
