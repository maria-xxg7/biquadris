#include "levelhard.h"

LevelHard::LevelHard(int level, string filename): BlockGenerator{level}, 
  filename{filename} {}

void LevelHard::newMove(shared_ptr<Board> b) {
  if (random) {
    int randNum;
    srand(time(NULL));
    randNum = rand() % 9;
    if (randNum < 2) {
      b->setBlockType(BlockType::SBlock);
    } else if (randNum < 4) {
      b->setBlockType(BlockType::ZBlock);
    } else {
      int randIndex;
      // srand(seed);
      randIndex = rand() % 5;
      vector<char> otherBlocks {'I', 'J', 'L', 'O', 'T'};
      b->setBlockType(stringToBlock(otherBlocks[randIndex]));
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
    b->setBlockType(stringToBlock(getBlockType));
  }
}
