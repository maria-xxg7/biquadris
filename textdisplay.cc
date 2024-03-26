#include "textdisplay.h"

TextDisplay::TextDisplay() {
  vector<char> row(boardWidth, ' ');
  for (int i = 0; i < boardHeight; ++i) {
    theDisplay.emplace_back(row);
  }
}

void TextDisplay::notify(Cell &c) {
  
}

BlockType TextDisplay::bType() {
  return BlockType::empty;
}

Row TextDisplay::rowType() {
  return Row::All;
}

TextDisplay::~TextDisplay() {}


ostream &operator<<(ostream &out, const TextDisplay &td) {
  // print out the game board
  for (int i = 0; i < td.boardHeight; ++i) {
    if (i >= td.reserved) { cout << '|'; }
    for (int j = 0; j < td.boardWidth; ++j) {
      cout << td.theDisplay[i][j];
    }
    cout << endl;
  }
  // print the bottom border
  cout << '+';
  for (int i = 0; i < td.boardWidth; ++i) { cout << '-'; }
  cout << endl;
  return out;
}
