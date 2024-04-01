#include "levelone.h"

LevelOne::LevelOne(bool playerNum, int level, Board &b, string filename): Player{playerNum, level, b}, 
          filename{filename} {
          level = 0;
}

void LevelOne::newMove(Board &b, bool playerTurn) {
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
  cout << "Current block type: " << getBlockType << endl;
  cout << "Next index: " << counter << endl;
}
