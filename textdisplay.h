#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
using namespace std;

class Cell;

class TextDisplay : public Observer {
    vector<vector<char>> theDisplay;
    const int boardWidth = 11;
    const int boardHeight = 15;
    const int reserved = 3;
  public:
    TextDisplay();
    void notify(Cell &c) override;
    BlockType bType() override;
    Row rowType() override;
    ~TextDisplay();
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
