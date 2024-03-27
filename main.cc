#include <iostream>
#include <string>
#include <sstream>
#include "board.h"
using namespace std;

int main() {
  Board b;
  b.init();
  b.moveBlock(BlockType::LBlock, "");
  // b.moveBlock("counterclockwise");
  // b.moveBlock("right");
  // // b.moveBlock("right");
  // b.moveBlock("clockwise");
  // b.moveBlock("left");
  // b.moveBlock("down");
  cout << b;
}
