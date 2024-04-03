#ifndef __CELL_H__
#define __CELL_H__
#include <vector>
#include "observer.h"
#include <memory>
using namespace std;

extern const int BOARD_W;
extern const int BOARD_H;
extern const int RESERVED;
extern const int BLOCK_DIM;

class Cell : public Observer {
    bool isFilled = false;
    vector<shared_ptr<Observer>> observers;
    vector<shared_ptr<Observer>> block;
    BlockType type;
    int row, col;
    vector<int> headCell = {0, 0};
    int cellLevel = 0;
  public:
    Cell(); // default constructor
    bool getState() const; // returns value of isFilled
    int getRow() const; // returns the value or row 
    int getCol() const; // returns the value of col
    int getHeadRow() const;
    int getHeadCol() const;
    int getLevel() const;
    void setFilled(); // Explicitly sets to filled
    void setUnfilled();
    void setCoords(int r, int c); // Sets the row and col location
    void setHead(int r, int c); 
    void setType(BlockType b); // Sets teh type of block the cell is part of
    void setLevel(int lvl); // Sets teh type of block the cell is part of
    int cellsLeft();
    void attach(shared_ptr<Observer> o);
    // void detach(Observer *o);
    void attachBlock(shared_ptr<Observer> o);
    void detachBlock(shared_ptr<Observer> o);

    BlockType bType() override;
    CellType cType() override;

    // Cells of the same row will call this and let the current cell (in the row)
    // to clear
    void notify(Cell &c) override; 
    void notifyAllObservers();
};

#endif
