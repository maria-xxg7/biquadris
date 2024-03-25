#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
using namespace std;

class Block;

class TextDisplay : public Observer {
    vector<vector<char>> theDisplay;
    const int boardWidth;
    const int boardHeight;
    const int reserved = 3;
    const int level;
  public:
    TextDisplay(int w, int h, int lvl);
    void notify(Block &b) override;
    ~TextDisplay();
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
