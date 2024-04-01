#include "graphicsdisplay.h"
#include "cell.h"

GraphicsDisplay::GraphicsDisplay(Xwindow &wd): wd{wd} {
    // draw background
  // size = wd.getWidth() / BOARD_W;
  size = 35;
  cout << "draw" << endl;
  wd.drawString(50, 50, "Level", Xwindow::Black);

  // draw board
  wd.fillRectangle(0, 0, 501, 751, Xwindow::DarkBlue);
  wd.fillRectangle(58, 60, 385, 630, Xwindow::Blue);
  wd.fillRectangle(0, 0, 10, 10, Xwindow::Coral);
  wd.fillRectangle(10, 10, 10, 10, Xwindow::DarkGreen);
  wd.fillRectangle(20, 20, 10, 10, Xwindow::LightGreen);
  wd.fillRectangle(30, 30, 10, 10, Xwindow::SkyBlue);
  wd.fillRectangle(40, 40, 10, 10, Xwindow::Purple);
  wd.fillRectangle(50, 50, 10, 10, Xwindow::Orange);
  wd.fillRectangle(60, 60, 10, 10, Xwindow::Yellow);
  wd.fillRectangle(70, 70, 10, 10, Xwindow::Brown);

  // fill in board grid pattern
  for (int i = 58; i < 443; i+=35) {
    for (int j = 60; j < 690; j+=35) {
      wd.fillRectangle(i+1, j+1, 33, 33, Xwindow::DarkestBlue);
      wd.drawRectangle(i, j, 35, 35, Xwindow::LightBlue);
    }
  }
}

void GraphicsDisplay::drawCell(Cell &c, int colour) {
  int outlineSize = 25;
  wd.fillRectangle(58 + 1 + c.getCol() * size, 60 + 1 + c.getRow() * size, size - 1, size - 1, colour);

  if (colour != Xwindow::DarkestBlue) {
    wd.fillRectangle(58 + 1 + 30 + c.getCol() * size, 60 + 1 + 6 + c.getRow() * size, 2, outlineSize, Xwindow::LightBlue);
    wd.fillRectangle(58 + 1 + 5 + c.getCol() * size, 60 + 1 + 30 + c.getRow() * size, outlineSize, 2, Xwindow::LightBlue);
  }
  if (colour == Xwindow::DarkestBlue) {
    wd.drawRectangle(58 + c.getCol() * size, 60 + c.getRow() * size, size, size, Xwindow::LightBlue);
  } else {
    wd.drawRectangle(58 + c.getCol() * size, 60 + c.getRow() * size, size, size, Xwindow::Blue);

  }
}

void GraphicsDisplay::notify(Cell &c) {

  // fill in board grid pattern
  switch(c.bType()) {
    case BlockType::IBlock:
      drawCell(c, Xwindow::SkyBlue);
      break;
    case BlockType::JBlock:
      drawCell(c, Xwindow::Purple);
      break;
    case BlockType::LBlock:
      drawCell(c, Xwindow::Coral);
      break;
    case BlockType::OBlock:
      drawCell(c, Xwindow::Orange);
      break;
    case BlockType::SBlock:
      drawCell(c, Xwindow::LightGreen);
      break;
    case BlockType::ZBlock:
      drawCell(c, Xwindow::DarkGreen);
      break;
    case BlockType::TBlock:
      drawCell(c, Xwindow::Yellow);
      break;
    case BlockType::empty:
      drawCell(c, Xwindow::DarkestBlue);
      break;
  }
}

BlockType GraphicsDisplay::bType() {
  return BlockType::empty;
}

CellType GraphicsDisplay::cType() {
  return CellType::All;
}

GraphicsDisplay::~GraphicsDisplay() {}
