#include "leveltwo.h"

LevelTwo::LevelTwo(bool playerNum, int level, Board &b): BlockGenerator{playerNum, level, b} {}

void LevelTwo::newMove(Board &b, bool playerTurn) {
  PRNG prng;
  int randOther = prng(11);
  vector<char> otherBlocks {'I', 'J', 'L', '0', 'S', 'Z', 'T'};
  b.setBlockType(stringToBlock(otherBlocks[randOther]));
}
