#include "leveltwo.h"

LevelTwo::LevelTwo(int level): BlockGenerator{level} {}

void LevelTwo::newMove(shared_ptr<Board> b) {
  int randNum;
  srand(time(NULL));
  randNum = rand() % 7;
  vector<char> otherBlocks {'I', 'J', 'L', 'O', 'S', 'Z', 'T'};
  b->setBlockType(stringToBlock(otherBlocks[randNum]));
}
