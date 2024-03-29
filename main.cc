#include <iostream>
#include <string>
#include <sstream>
#include "board.h"
using namespace std;

int main() {
  Board b;
  b.init();
  b.setBlockType(BlockType::LBlock); // use this to set the block type for the next block :)
  b.moveBlock("");
  // b.moveBlock("clockwise");
  // b.moveBlock("clockwise");
  // // // b.moveBlock("right");
  b.moveBlock("save");
  b.dropBlock();
  b.setBlockType(BlockType::SBlock);
  // cout << "new block" << endl;
  b.moveBlock("");
  // b.moveBlock("right");
  b.moveBlock("save");
  b.dropBlock();

  b.setBlockType(BlockType::IBlock);
  b.moveBlock("");
  b.moveBlock("clockwise");
  b.moveBlock("save");
  b.dropBlock();

  b.setBlockType(BlockType::TBlock);
  b.moveBlock("");
  b.moveBlock("counterclockwise");
  b.moveBlock("right");
  b.moveBlock("right");
  b.moveBlock("right");
  b.moveBlock("right");
  b.moveBlock("right");
  b.moveBlock("right");
  b.moveBlock("right");
  b.moveBlock("save");
  b.dropBlock();

  cout << b;
}
