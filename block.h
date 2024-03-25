#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <iostream>
#include <vector>
#include "observer.h"
using namespace std; 

class Block : public Observer {
    int row, col;
    vector<Observer*> observers;

  public:
    Block(); // default constructor

    void setCoords(int row, int col);
    int getRow() const;
    int getCol() const;

    // made virtual in block class since each subclass will set which type of block
    virtual BlockType bType() override;

    void notifyObservers(); 
    void attatch(Observer *o);

    virtual void rotateBlock(bool clockwise) = 0;
    virtual void shiftBlock(string dir) = 0;
    
};

#endif
