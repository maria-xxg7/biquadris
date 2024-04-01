#include "levelthree.h"

LevelThree::LevelThree(bool playerNum, int level, Board &b, string filename): Player{playerNum, level, b}, 
  filename{filename} {}

void LevelThree::newMove(Board &b, bool playerTurn) {
  if (random) {
    PRNG prng;
    int randOther = prng(8); 
    if (randOther < 2) {
      b.setBlockType(BlockType::SBlock);
    } else if (randOther < 4) {
      b.setBlockType(BlockType::ZBlock);
    } else {
      int randIndex = prng(4);
      vector<char> otherBlocks {'I', 'J', 'L', '0', 'T'};
      b.setBlockType(stringToBlock(otherBlocks[randOther]));
    }
  } else {
    int index = 0;
    char getBlockType;
    string sequence;
    ifstream sequenceList (filename);
    getline(sequenceList, sequence);
    istringstream getNext{sequence};
    getNext >> getBlockType;
    while (index != counter) {
      if (getNext >> getBlockType) {
        ++index;
      } else {
        getNext.clear();
        getNext.seekg(0);
        getNext >> getBlockType;
        counter = 0;
        break;
      }
    }
    ++counter;
    b.setBlockType(stringToBlock(getBlockType));
  }
}
