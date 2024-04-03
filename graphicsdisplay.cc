#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay(Xwindow &wd): wd{wd} {
  wd.fillRectangle(0, 0, wd.getWidth(), wd.getHeight(), Xwindow::DarkBlue);
  wd.fillRectangle(spacing - 1, spacing - 1, gridWidth + 3, gridHeight + 3, Xwindow::LightBlue);
  wd.fillRectangle(spacing, spacing, gridWidth, gridHeight, Xwindow::DarkestBlue);
  wd.fillRectangle(nextSpaceW - 1, nextSpaceH - 1, nextWidth + 3, nextWidth + 3, Xwindow::LightBlue);
  wd.fillRectangle(nextSpaceW, nextSpaceH, nextWidth, nextWidth, Xwindow::DarkestBlue);

  wd.drawString(spacing, nextSpaceH + spacing/2, "Level: ", Xwindow::White);
  wd.drawString(spacing + spacing, nextSpaceH + spacing/2, to_string(level), Xwindow::White);
  wd.drawString(spacing, nextSpaceH + spacing + 10, "Score: ", Xwindow::White);
  wd.drawString(spacing + spacing, nextSpaceH + spacing + 10, to_string(score), Xwindow::White);
  wd.drawString(spacing, nextSpaceH + spacing * 2, "High Score: ", Xwindow::White);
  wd.drawString(spacing + spacing * 2 - 10, nextSpaceH + spacing * 2, to_string(hiScore), Xwindow::White);

  wd.drawString(nextSpaceW, nextSpaceH - spacing/2 + 5, "Next Block: ", Xwindow::White);

  // fill in board grid pattern
  for (int i = spacing; i < gridWidth + spacing ; i += cellSize) {
    for (int j = spacing; j < gridHeight + spacing; j += cellSize) {
      wd.drawRectangle(i, j, cellSize, cellSize, Xwindow::LightBlue);
    }
  }

  for (int i = nextSpaceW; i < nextWidth + nextSpaceW ; i += cellSize) {
    for (int j = nextSpaceH; j < nextWidth + nextSpaceH; j += cellSize) {
      wd.drawRectangle(i, j, cellSize, cellSize, Xwindow::LightBlue);
    }
  }
  curType = BlockType::empty;
}

void GraphicsDisplay::drawCell(Cell &c, int locW, int locH, int colour) {
  if (colour != Xwindow::DarkestBlue) {
    wd.fillRectangle(locW + 1 + c.getCol() * cellSize, locH + 1 + c.getRow() * cellSize, cellSize, cellSize, colour + 1);
    wd.fillRectangle(locW + 1 + 5 + c.getCol() * cellSize, locH + 1 + 5 + c.getRow() * cellSize, cellSize - 5, cellSize - 5, colour);
  } else {
    wd.fillRectangle(locW + 1 + c.getCol() * cellSize, locH + 1 + c.getRow() * cellSize, cellSize, cellSize, colour);
  }

  if (colour != Xwindow::DarkestBlue) {
    wd.fillRectangle(locW + 1 + 22 + c.getCol() * cellSize, locH + 1 + 8 + c.getRow() * cellSize, 2, outlineSize * 2 - 3, Xwindow::LightBlue);
    wd.fillRectangle(locW + 1 + 4 + c.getCol() * cellSize, locH + 1 + 23 + c.getRow() * cellSize, outlineSize * 2 - 1, 2, Xwindow::LightBlue);
    wd.fillRectangle(locW + 1 + 22 + c.getCol() * cellSize, locH + 1 + 4 + c.getRow() * cellSize, 2, 2, Xwindow::LightBlue);
  }
  
  if (colour == Xwindow::DarkestBlue || colour == Xwindow::Grey) {
    wd.drawRectangle(locW + c.getCol() * cellSize, locH + c.getRow() * cellSize, cellSize, cellSize, Xwindow::LightBlue);
  } else {
    wd.drawRectangle(locW + c.getCol() * cellSize, locH + c.getRow() * cellSize, cellSize, cellSize, Xwindow::Blue);
  }
}

void GraphicsDisplay::updateNext(shared_ptr<Block> block, BlockType b) {
  if (curType == b) { return; }

  vector<Cell> tempBlock;
  vector<vector<char>> charBlock = (*block).getConfig();
  for (int i = 0; i < BLOCK_DIM; ++i) {
    for (int j = 0; j < BLOCK_DIM; ++j) {
      if (charBlock[i][j] != ' ') {
        Cell c;
        c.setCoords(i, j);
        tempBlock.emplace_back(c);
      }
    }
  }

  for (int i = nextSpaceW; i < nextWidth + nextSpaceW ; i += cellSize) {
    for (int j = nextSpaceH; j < nextWidth + nextSpaceH; j += cellSize) {
      wd.fillRectangle(i, j, cellSize, cellSize, Xwindow::DarkestBlue);
      wd.drawRectangle(i, j, cellSize, cellSize, Xwindow::LightBlue);
    }
  }

  switch(b) {
    case BlockType::IBlock:
      for (int i = 0; i < BLOCK_DIM; ++i) {
        drawCell(tempBlock[i], nextSpaceW, nextSpaceH, Xwindow::SkyBlue);
      }
      break;
    case BlockType::JBlock:
      for (int i = 0; i < BLOCK_DIM; ++i) {
        drawCell(tempBlock[i], nextSpaceW, nextSpaceH, Xwindow::Purple);
      }
      break;
    case BlockType::LBlock:
      for (int i = 0; i < BLOCK_DIM; ++i) {
        drawCell(tempBlock[i], nextSpaceW, nextSpaceH, Xwindow::Coral);
      }        
      break;
    case BlockType::OBlock:
      for (int i = 0; i < BLOCK_DIM; ++i) {
        drawCell(tempBlock[i], nextSpaceW, nextSpaceH, Xwindow::Orange);
      }        
      break;
    case BlockType::SBlock:
      for (int i = 0; i < BLOCK_DIM; ++i) {
        drawCell(tempBlock[i], nextSpaceW, nextSpaceH, Xwindow::LightGreen);
      }        
      break;
    case BlockType::ZBlock:
      for (int i = 0; i < BLOCK_DIM; ++i) {
        drawCell(tempBlock[i], nextSpaceW, nextSpaceH, Xwindow::DarkGreen);
      }        
      break;
    case BlockType::TBlock:
      for (int i = 0; i < BLOCK_DIM; ++i) {
        drawCell(tempBlock[i], nextSpaceW, nextSpaceH, Xwindow::Yellow);
      }        
      break;
    case BlockType::empty:
      break;
  }
  curType = b;
}

void GraphicsDisplay::setScore(int s) { 
  if (score == s) { return; }
  wd.drawString(spacing + spacing, nextSpaceH + spacing + 10, to_string(score), Xwindow::DarkBlue);
  wd.drawString(spacing + spacing, nextSpaceH + spacing + 10, to_string(s), Xwindow::White);
  score = s; 
}

void GraphicsDisplay::setHiScore(int hs) { 
  if (hiScore == hs) { return; }
  wd.drawString(spacing + spacing * 2 - 10, nextSpaceH + spacing * 2, to_string(hiScore), Xwindow::DarkBlue);
  wd.drawString(spacing + spacing * 2 - 10, nextSpaceH + spacing * 2, to_string(hs), Xwindow::White);
  hiScore = hs; 
}

void GraphicsDisplay::setLevel(int l) { 
  if (level == l) { return; }
  wd.drawString(spacing + spacing, nextSpaceH + spacing/2, to_string(level), Xwindow::DarkBlue);
  wd.drawString(spacing + spacing, nextSpaceH + spacing/2, to_string(l), Xwindow::White);
  level = l; 
}

void GraphicsDisplay::notify(Cell &c) {
  // fill in board grid pattern
  if (c.getState() && !c.getHidden()) {
    switch(c.bType()) {
      case BlockType::IBlock:
        drawCell(c, spacing, spacing, Xwindow::SkyBlue);
        break;
      case BlockType::JBlock:
        drawCell(c, spacing, spacing, Xwindow::Purple);
        break;
      case BlockType::LBlock:
        drawCell(c, spacing, spacing, Xwindow::Coral);
        break;
      case BlockType::OBlock:
        drawCell(c, spacing, spacing, Xwindow::Orange);
        break;
      case BlockType::SBlock:
        drawCell(c, spacing, spacing, Xwindow::LightGreen);
        break;
      case BlockType::ZBlock:
        drawCell(c, spacing, spacing, Xwindow::DarkGreen);
        break;
      case BlockType::TBlock:
        drawCell(c, spacing, spacing, Xwindow::Yellow);
        break;
      case BlockType::empty:
        drawCell(c, spacing, spacing, Xwindow::DarkestBlue);
        break;
    }
  } else {
    if (c.getHidden()) {
      drawCell(c, spacing, spacing, Xwindow::Grey);
    } else {
      drawCell(c, spacing, spacing, Xwindow::DarkestBlue);
    }
  }
}

BlockType GraphicsDisplay::bType() {
  return BlockType::empty;
}

CellType GraphicsDisplay::cType() {
  return CellType::All;
}

GraphicsDisplay::~GraphicsDisplay() {}
