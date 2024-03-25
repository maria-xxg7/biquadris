#include "textdisplay.h"

TextDisplay::TextDisplay(int w, int h, int lvl): boardWidth{w}, boardHeight{h}, 
  level{lvl} {
  vector<char> row(boardWidth, ' ');
  for (int i = 0; i < boardHeight; ++i) {
    theDisplay.emplace_back(row);
  }
}

void TextDisplay::notify(Block &b) {
  
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  // print level and score (move to board class)
  // string level = "Level:";
  // string score = "Score:";
  // cout << level;
  // for (int i = level.size(); i < td.boardWidth - 1; ++i) {
  //   cout << ' ' << td.level << 3endl;
  // }
  // cout << score;
  // for (int i = score.size(); i < td.boardWidth - 1; ++i) {

  // }

  // print border
  for (int i = 0; i < td.boardWidth; ++i) { cout << '-'; }

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
