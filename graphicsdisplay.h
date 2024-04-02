#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include "window.h"
#include "observer.h"
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
  void drawCell(Cell &c, int colour);

  public:
    GraphicsDisplay(Xwindow &wd);
    void notify(Cell &c) override;
    BlockType bType() override;
    CellType cType() override;
    ~GraphicsDisplay();
};

#endif
