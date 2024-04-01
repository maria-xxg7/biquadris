#include "levelone.h"

LevelOne::LevelOne(bool playerNum, int level, Board &b): BlockGenerator{playerNum, level, b} {}

void LevelOne::newMove(Board &b, bool playerTurn) {
  PRNG prng;
  int randNum = prng(11);
  
  if (randNum < 2) {
    b.setBlockType(BlockType::ZBlock);
  } else if (randNum < 4) {
    b.setBlockType(BlockType::SBlock);
  } else {
    int randOther = prng(4);
    vector<char> otherBlocks {'I', 'J', 'L', '0'};
    b.setBlockType(stringToBlock(otherBlocks[randOther]));
  }
}
