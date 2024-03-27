#include <iostream>
#include <string>
#include <sstream>
#include "board.h"
using namespace std;

int main() {
  Board b;
  b.init();
  b.moveBlock("");
  cout << b;

  // b.moveBlock("counterclockwise");
  b.moveBlock("right");
  cout << b;

  // b.moveBlock("right");
  // b.moveBlock("clockwise");
  // b.moveBlock("left");
  // b.moveBlock("down");
  // cout << b;
}
