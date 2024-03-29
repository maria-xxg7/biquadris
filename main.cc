#include <iostream>
#include <string>
#include <sstream>
#include "board.h"
using namespace std;

int main() {
  Board b;
  b.init();
  b.setBlockType(BlockType::TBlock); // use this to set the block type for the next block :)
  b.moveBlock("");
  cout << b;
  b.moveBlock("counterclockwise");
   cout << b;
  b.moveBlock("right");
  b.moveBlock("save");
  b.dropBlock();
  cout << b;

  b.setBlockType(BlockType::TBlock); // use this to set the block type for the next block :)
  b.moveBlock("");
  cout << b;
  b.moveBlock("clockwise");
  cout << b;
  b.moveBlock("clockwise");
  b.moveBlock("clockwise");
  b.moveBlock("right");
   cout << b;
  b.moveBlock("right");
   cout << b;
  b.moveBlock("right");
   cout << b;
  b.moveBlock("right");
   cout << b;
  b.moveBlock("save");
  b.dropBlock();
  cout << b;
}
