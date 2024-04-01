#include "graphicsdisplay.h"
#include "cell.h"

GraphicsDisplay::GraphicsDisplay(Xwindow &w): w{w} {
}

void GraphicsDisplay::notify(Cell &c) {
  // switch(c.bType()) {
  //   case BlockType::IBlock:
  //     theDisplay[c.getRow()][c.getCol()] = 'I';
  //     break;
  //   case BlockType::JBlock:
  //     theDisplay[c.getRow()][c.getCol()] = 'J';
  //     break;
  //   case BlockType::LBlock:
  //     theDisplay[c.getRow()][c.getCol()] = 'L';
  //     break;
  //   case BlockType::OBlock:
  //     theDisplay[c.getRow()][c.getCol()] = 'O';
  //     break;
  //   case BlockType::SBlock:
  //     theDisplay[c.getRow()][c.getCol()] = 'S';
  //     break;
  //   case BlockType::ZBlock:
  //     theDisplay[c.getRow()][c.getCol()] = 'Z';
  //     break;
  //   case BlockType::TBlock:
  //     theDisplay[c.getRow()][c.getCol()] = 'T';
  //     break;
  //   case BlockType::empty:
  //     // cout << "(" << c.getRow() << "," << c.getCol() << ")" << endl;
  //     theDisplay[c.getRow()][c.getCol()] = '.';
  //     break;
  // }
}

BlockType GraphicsDisplay::bType() {
  return BlockType::empty;
}

CellType GraphicsDisplay::cType() {
  return CellType::All;
}

GraphicsDisplay::~GraphicsDisplay() {}
