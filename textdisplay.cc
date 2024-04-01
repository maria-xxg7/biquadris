#include "textdisplay.h"

TextDisplay::TextDisplay() {
  vector<char> row(BOARD_W, '.');
  for (int i = 0; i < BOARD_H + RESERVED; ++i) {
    theDisplay.emplace_back(row);
  }
}

void TextDisplay::notify(Cell &c) {
    switch(c.bType()) {
      case BlockType::IBlock:
        theDisplay[c.getRow()][c.getCol()] = 'I';
        break;
      case BlockType::JBlock:
        theDisplay[c.getRow()][c.getCol()] = 'J';
        break;
      case BlockType::LBlock:
        theDisplay[c.getRow()][c.getCol()] = 'L';
        break;
      case BlockType::OBlock:
        theDisplay[c.getRow()][c.getCol()] = 'O';
        break;
      case BlockType::SBlock:
        theDisplay[c.getRow()][c.getCol()] = 'S';
        break;
      case BlockType::ZBlock:
        theDisplay[c.getRow()][c.getCol()] = 'Z';
        break;
      case BlockType::TBlock:
        theDisplay[c.getRow()][c.getCol()] = 'T';
        break;
      case BlockType::empty:
        theDisplay[c.getRow()][c.getCol()] = '.';
        break;
    }
}

BlockType TextDisplay::bType() {
  return BlockType::empty;
}

CellType TextDisplay::cType() {
  return CellType::All;
}

TextDisplay::~TextDisplay() {}


ostream &operator<<(ostream &out, const TextDisplay &td) {
  // print out the game board
  for (int i = 0; i < BOARD_H + RESERVED; ++i) {

    if (i >= RESERVED) { cout << '|'; }
    else { cout << ' '; }
    for (int j = 0; j < BOARD_W; ++j) {
      cout << td.theDisplay[i][j];
    }
    cout << endl;
  }
  // print the bottom border
  cout << '+';
  for (int i = 0; i < BOARD_W; ++i) { cout << '-'; }
  cout << endl;
  return out;
}
