#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include "window.h"
#include "observer.h"
#include <iostream>

class Cell;

class GraphicsDisplay : public Observer {
    Xwindow &w; // window
    int gridSize; // size of grid
    int windowSize; // window size
    int size; // size of square in grid
    public:
        GraphicsDisplay(Xwindow &w);
        void notify(Cell &c) override;
        BlockType bType() override;
        CellType cType() override;
        ~GraphicsDisplay();
};
#endif
