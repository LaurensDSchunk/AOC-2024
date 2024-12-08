#include "utils.h"
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void placeAntinodes(vector<vector<bool>> &antinodePositions,
                    vector<pair<int, int>> &placements,
                    vector<vector<char>> &layout, char antenna) {
  int width = antinodePositions.at(0).size();
  int height = antinodePositions.size();
  for (int i = 0; i < placements.size(); i++) {
    for (int j = 0; j < placements.size(); j++) {
      if (i != j) {
        pair<int, int> pos1 = placements.at(i), pos2 = placements.at(j);

        pair<int, int> diff = {pos2.first - pos1.first,
                               pos2.second - pos1.second};

        pair<int, int> newPos = {pos2.first - diff.first,
                                 pos2.second - diff.second};
        while (newPos.first >= 0 && newPos.first < width &&
               newPos.second >= 0 && newPos.second < height) {
          antinodePositions.at(newPos.second).at(newPos.first) = true;
          newPos = {newPos.first - diff.first,
                    newPos.second - diff.second}; // Update newPos correctly
        }
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

  vector<vector<char>> layout;
  map<char, vector<pair<int, int>>>
      antennas; // {Antenna char, list of positions}

  string line;
  int currentLine = 0;
  while (getline(file, line)) {
    vector<char> lineVec(line.length());

    for (int i = 0; i < line.length(); i++) {
      char c = line[i];
      lineVec.at(i) = c;
      if (c != '.') {
        // Antenna at position
        antennas[c].push_back({i, currentLine});
      }
    }
    layout.push_back(lineVec);
    currentLine++;
  }

  int mapHeight = layout.size();
  int mapWidth = layout.at(0).size();

  vector<vector<bool>> positions(mapHeight, vector<bool>(mapWidth));

  for (auto &[key, val] : antennas) {
    placeAntinodes(positions, val, layout, key);
  }

  int total = 0;
  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      if (positions.at(y).at(x)) {
        total++;
      }
    }
  }
  cout << total << endl;
  return 0;
}
