#include "textdisplay.h"

TextDisplay::TextDisplay() {
  vector<char> row(boardWidth, ' ');
  for (int i = 0; i < boardHeight; ++i) {
    theDisplay.emplace_back(row);
  }
}

void TextDisplay::notify(Cell &c) {
  if (c.getState()) {
    theDisplay[c.getRow()][c.getCol()] = 'J';
  }
}

BlockType TextDisplay::bType() {
  return BlockType::empty;
}

RowType TextDisplay::rType() {
  return RowType::All;
}

TextDisplay::~TextDisplay() {}


ostream &operator<<(ostream &out, const TextDisplay &td) {
  // print out the game board
  for (int i = 0; i < td.boardHeight; ++i) {

    if (i >= td.reserved) { cout << '|'; }
    else { cout << ' '; }
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
