#include "graphicsdisplay.h"
#include "cell.h"

GraphicsDisplay::GraphicsDisplay(Xwindow &wd): wd{wd} {
  wd.fillRectangle(0, 0, wd.getWidth(), wd.getHeight(), Xwindow::DarkBlue);
  wd.fillRectangle(spacing - 1, spacing - 1, gridWidth + 3, gridHeight + 3, Xwindow::LightBlue);
  wd.fillRectangle(spacing, spacing, gridWidth, gridHeight, Xwindow::DarkestBlue);
  wd.fillRectangle(nextSpaceW - 1, nextSpaceH - 1, nextWidth + 3, nextWidth + 3, Xwindow::LightBlue);
  wd.fillRectangle(nextSpaceW, nextSpaceH, nextWidth, nextWidth, Xwindow::DarkestBlue);

  wd.drawString(spacing, nextSpaceH + spacing/2, "Level: ", Xwindow::White);
  wd.drawString(spacing, nextSpaceH + spacing + 10, "Score: ", Xwindow::White);
  wd.drawString(nextSpaceW, nextSpaceH - spacing/2 + 5, "Next Block: ", Xwindow::White);

  // fill in board grid pattern
  for (int i = spacing; i < gridWidth + spacing ; i += cellSize) {
    for (int j = spacing; j < gridHeight + spacing; j += cellSize) {
      wd.fillRectangle(i + 1, j + 1, cellSize - 2, cellSize - 2, Xwindow::DarkestBlue);
      wd.drawRectangle(i, j, cellSize, cellSize, Xwindow::LightBlue);
    }
  }

  for (int i = nextSpaceW; i < nextWidth + nextSpaceW ; i += cellSize) {
    for (int j = nextSpaceH; j < nextWidth + nextSpaceH; j += cellSize) {
      wd.fillRectangle(i + 1, j + 1, cellSize - 2, cellSize - 2, Xwindow::DarkestBlue);
      wd.drawRectangle(i, j, cellSize, cellSize, Xwindow::LightBlue);
    }
  }
}

void GraphicsDisplay::drawCell(Cell &c, int colour) {
  // if (colour == Xwindow::Coral) {
  //   wd.fillRectangle(spacing + c.getCol() * cellSize, 60 + c.getRow() * cellSize, cellSize, cellSize, Xwindow::DCoral);
  //   wd.fillRectangle(58 + 5 + c.getCol() * cellSize, 60 + 5 + c.getRow() * cellSize, cellSize - 5, cellSize - 5, Xwindow::Coral);
  wd.fillRectangle(spacing + 1 + c.getCol() * cellSize, spacing + 1 + c.getRow() * cellSize, cellSize, cellSize, colour);

  // if (colour != Xwindow::DarkestBlue) {
  //   wd.fillRectangle(58 + 1 + 30 + c.getCol() * cellSize, 60 + 1 + 10 + c.getRow() * cellSize, 2, outlineSize, Xwindow::LightBlue);
  //   wd.fillRectangle(58 + 1 + 7 + c.getCol() * cellSize, 60 + 1 + 30 + c.getRow() * cellSize, outlineSize, 2, Xwindow::LightBlue);
  // }
  
  if (colour == Xwindow::DarkestBlue) {
    wd.drawRectangle(spacing + c.getCol() * cellSize, spacing + c.getRow() * cellSize, cellSize, cellSize, Xwindow::LightBlue);
  } else {
    wd.drawRectangle(spacing + c.getCol() * cellSize, spacing + c.getRow() * cellSize, cellSize, cellSize, Xwindow::Blue);
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
