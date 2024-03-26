#include "board.h"

Board::Board() : theBoard {}, level {0}, curScore {0}, highScore {0}, 
  nextBlock{}, curBlock{}, td{new TextDisplay{}} //, gd{nullptr}
  {}

Board::~Board() {
  delete td;
  // delete gd;
}

void Board::clearBoard() {
  theBoard.clear();
  curScore = 0;
  nextBlock = BlockType::empty; // how to reset them to nothing?
  curBlock = BlockType::empty;
}

void Board::init() {
  delete td;
  //delete gd;
  td = new TextDisplay();
  // gd = new GraphicsDisplay(graphics, gridSize); 

  vector<Cell> new_row (boardWidth, Cell());
  for (int grid_r = 0; grid_r < boardHeight + reserved; ++grid_r) {
    theBoard.emplace_back(new_row);
  }

  for (int row = 0; row < boardHeight + reserved; ++row) {
    for (int col = 0; col < boardWidth; ++col) {

      theBoard[row][col].setCoords(row, col);

      theBoard[row][col].attach(td);
      //theBoard[row][col].attach(gd);
      
      for (int ob = 0; ob < boardWidth; ++ob) {
        if (ob != col) {
          theBoard[row][col].attach(&theBoard[row][ob]);
        }
      }
    }
  }
}



ostream &operator<<(ostream &out, const Board &b) {
  //print level and score (move to board class)
  string level = "Level:";
  string score = "Score:";
  out << level << endl;
  out << score << endl;
  out << *b.td;
  return out;
}
