#include "levelzero.h"

LevelZero::LevelZero(string filename, int level, int counter): BlockGenerator{level}, filename{filename}, counter{counter} {}

void LevelZero::newMove(shared_ptr<Board> b) {
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
  b->setBlockType(BlockType::JBlock);
  // cout << "Current block type: " << getBlockType << endl;
  // cout << "Next index: " << counter << endl;
}
