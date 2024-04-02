#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include "cell.h"
using namespace std;

class Cell;

class TextDisplay : public Observer{
    vector<vector<char>> theDisplay;
  public:
    TextDisplay();
    void notify(Cell &c) override;
    BlockType bType() override;
    CellType cType() override;

    ~TextDisplay();
    friend ostream &operator<<(ostream &out, const TextDisplay &td);
};

#endif
