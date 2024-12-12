#include "utils.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  ifstream file(argv[1]);
  if (!file) {
    cerr << "Error: Unable to open file" << endl;
    return 1;
  }
}
