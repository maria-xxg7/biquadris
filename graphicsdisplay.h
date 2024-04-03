#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include "window.h"
#include "observer.h"
#include "cell.h"
#include "block.h"
#include <memory>
#include <iostream>

class Cell;

class GraphicsDisplay : public Observer {
  Xwindow &wd; // window
  int cellSize = 28; // size of square in grid
  int nextWidth = 112;
  int gridWidth = 308;
  int gridHeight = 504;
  int spacing = 40;
  int nextSpaceW = spacing + gridWidth - nextWidth;
  int nextSpaceH = gridHeight + spacing * 2;
  int outlineSize = 10;
  void drawCell(Cell &c, int locW, int locH, int colour);
  BlockType curType;
  int score = 0;
  int level = 0;

  public:
    GraphicsDisplay(Xwindow &wd);
    void updateNext(shared_ptr<Block> block, BlockType b);
    void setScore(int s);
    void setLevel(int l);
    void notify(Cell &c) override;
    BlockType bType() override;
    CellType cType() override;
    ~GraphicsDisplay();
};

#endif
