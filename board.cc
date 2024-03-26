#include "board.h"

Board::Board() : theBoard {}, level {0}, curScore {0}, highScore {0}, 
  nextBlock{}, curBlock{}, td{new TextDisplay{0}} //, gd{nullptr}
  {}

Board::~Board() {
  delete td;
  // delete gd;
}

void Board::clearBoard() {
  theBoard.clear();
  curScore = 0;
  nextBlock; // how to reset them to nothing?
  curBlock;
}

void Board::init() {
  delete td;
  //delete gd;
  td = new TextDisplay();
  // gd = new GraphicsDisplay(graphics, gridSize); 

  vector<Cell> new_row (width, Cell());
  for (int grid_r = 0; grid_r < width; ++grid_r) {
    theBoard.emplace_back(new_row);
  }

  for (int row = 0; row < width; ++row) {
    for (int col = 0; col < height; ++col) {

      theBoard[row][col].setCoords(row, col);

      theBoard[row][col].attach(td);
      //theBoard[row][col].attach(gd);

      
    }
  }

}

ostream &operator<<(ostream &out, const Board &b) {
  //print level and score (move to board class)
  string level = "Level:";
  string score = "Score:";
  cout << level;
  for (int i = level.size(); i < td.boardWidth - 1; ++i) {
    cout << ' ' << td.level << endl;
  }
  cout << score;
  for (int i = score.size(); i < td.boardWidth - 1; ++i) {

  }
}
