#ifndef __CELL_H__
#define __CELL_H__
#include <vector>
#include "observer.h"
using namespace std;

class Cell : public Observer {
    bool isFilled = false;
    vector<Observer*> observers; // 
    BlockType type = BlockType::empty;
    int row, col;
  public:
    Cell(); // default constructor
    bool getState() const; // returns value of isFilled
    int getRow() const; // returns the value or row 
    int getCol() const; // returns the value of col
    void setFilled(); // Explicitly sets to filled
    void setCoords(int r, int c); // Sets the row and col location
    void setType(BlockType b); // Sets teh type of block the cell is part of
    
    void attach(Observer *o);

    BlockType bType() override;
    // Cells of the same row will call this and let the current cell (in the row)
    // to clear
    void notify(Cell &c) override; 
    void notifyAllObservers();
};

#endif
