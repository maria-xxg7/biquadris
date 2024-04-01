#include "graphicsdisplay.h"
#include "cell.h"

GraphicsDisplay::GraphicsDisplay(Xwindow &wd): wd{wd} {
    // draw background
    cout << "draw" << endl;
  wd.drawString(50, 50, "Level", Xwindow::Black);

  // draw board
  wd.fillRectangle(58, 113, 385, 525, Xwindow::White);

  // fill in board grid pattern
  for (int i = 58; i < 443; i+=35) {
    for (int j = 113; j < 638; j+=35) {
      wd.drawRectangle(i, j, 35, 35, Xwindow::Black);
      wd.fillRectangle(i+1, j+1, 33, 33, Xwindow::White);
    }
  }
}

void GraphicsDisplay::notify(Cell &c) {
  // fill in board grid pattern
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
