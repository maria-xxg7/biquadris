#include "levelone.h"

LevelOne::LevelOne(int level): BlockGenerator{level} {}

void LevelOne::newMove(shared_ptr<Board> b) {
  int randNum;
  srand(time(NULL));
  randNum = rand() % 12;
  if (randNum == 1) {
    b->setBlockType(BlockType::ZBlock);
  } else if (randNum == 2) {
    b->setBlockType(BlockType::SBlock);
  } else {
    int randOther;
    srand(time(NULL));
    randOther = rand() % 5;
    vector<char> otherBlocks {'I', 'J', 'L', 'O', 'T'};
    b->setBlockType(stringToBlock(otherBlocks[randOther]));
  }
}
