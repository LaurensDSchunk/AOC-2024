#include "utils.h"

bool canReachPrize(pair<int, int> buttonA, pair<int, int> buttonB,
                   pair<long int, long int> prize, int &n_A, int &n_B) {
  for (n_A = 0;; n_A++) {

    int Xleft = prize.first - n_A * buttonA.first;
    int Yleft = prize.second - n_A * buttonA.second;

    if (Xleft % buttonB.first == 0 && Yleft % buttonB.second == 0) {
      int n1 = Xleft / buttonB.first;
      int n2 = Yleft / buttonB.second;

      if (n1 == n2) {
        n_B = Xleft / buttonB.first;

        return true;
      }
    }

    if (buttonA.first * n_A > prize.first ||
        buttonA.second * n_A > prize.second) {
      break;
    }
  }
  return 0;
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

  vector<vector<pair<int, int>>> machines;
  machines.push_back({});

  regex pattern(R"(X[+=](\d+), Y[+=](\d+))");
  smatch matches;

  string line;
  int currMachine = 0;
  int stage = 1;

  while (getline(file, line)) {
    if (regex_search(line, matches, pattern)) {
      int num1 = stoi(matches[1].str());
      int num2 = stoi(matches[2].str());

      pair<int, int> newPair = {num1, num2};
      machines.at(currMachine).push_back(newPair);
    }

    stage++;
    if (stage > 3) {
      // After every 3 lines, add a new machine and reset stage
      file.ignore();
      currMachine++;
      machines.push_back({});
      stage = 0;
    }
  }

  long int total = 0;

  for (int m = 0; m < machines.size(); m++) {
    pair<int, int> buttonAOffset = machines.at(m).at(0);
    pair<int, int> buttonBOffset = machines.at(m).at(1);
    pair<long int, long int> prizePos = machines.at(m).at(2);

    prizePos.first += 10000000000000;
    prizePos.second += 10000000000000;

    cout << "machine " << m + 1 << "\n"
         << buttonAOffset.first << " " << buttonAOffset.second << endl;
    cout << buttonBOffset.first << " " << buttonBOffset.second << endl;
    cout << prizePos.first << " " << prizePos.second << endl;

    int n_A, n_B;
    if (canReachPrize(buttonAOffset, buttonBOffset, prizePos, n_A, n_B)) {
      total += n_A * 3;
      total += n_B;
    }
  }

  cout << total << endl;
  return 0;
}
