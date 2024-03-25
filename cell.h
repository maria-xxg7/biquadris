#ifndef __CELL_H__
#define __CELL_H__
#include <vector>
#include "observer.h"
using namespace std;

class Cell : public Observer {
    bool isOn = false;
    vector<Observer*> observers;
    int row, col;
  public:
    Cell();
    bool getState() const;
    int getRow() const;
    int getCol() const;
    void setOn();
    void setCoords(int r, int c);
    void attach(Observer *o);

    BlockType bType() override;
    void notify(Cell &c) override;
    void notifyAllObservers();
};

#endif