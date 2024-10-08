#ifndef __CELL_H__
#define __CELL_H__
#include <vector>
#include "observer.h"
using namespace std;

extern const int BOARD_W;
extern const int BOARD_H;
extern const int RESERVED;
extern const int BLOCK_DIM;

class Cell : public Observer {
    bool isFilled = false;
    vector<Observer*> observers;
    vector<Observer*> block;
    BlockType type;
    int row, col;
    vector<int> headCell = {0, 0};
    int cellLevel = 0;
    bool hidden = false;
  public:
    Cell(); // default constructor
    bool getState() const; // returns value of isFilled
    bool getHidden() const;
    int getRow() const; // returns the value or row 
    int getCol() const; // returns the value of col
    int getHeadRow() const;
    int getHeadCol() const;
    int getLevel() const;
    void setFilled(); // Explicitly sets to filled
    void setUnfilled();
    void hide();
    void show();
    void setCoords(int r, int c); // Sets the row and col location
    void setHead(int r, int c); 
    void setType(BlockType b); // Sets teh type of block the cell is part of
    void setLevel(int lvl); // Sets teh type of block the cell is part of
    int cellsLeft();
    void attach(Observer *o);
    void detach(Observer *o);
    void attachBlock(Observer *o);
    void detachBlock(Observer *o);

    BlockType bType() override;
    CellType cType() override;

    // Cells of the same row will call this and let the current cell (in the row)
    // to clear
    void notify(Cell &c) override; 
    void notifyAllObservers();
};

#endif
