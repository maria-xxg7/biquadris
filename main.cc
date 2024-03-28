#include <iostream>
#include <string>
#include <sstream>
#include "board.h"
using namespace std;

int main() {
  Board b;
  b.init();
  b.moveBlock("");
  b.moveBlock("clockwise");
  b.moveBlock("right");
  b.moveBlock("save");
  b.dropBlock();
  cout << b;
}
