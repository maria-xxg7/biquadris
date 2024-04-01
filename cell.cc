#include "cell.h"
#include <iostream>
using namespace std;

Cell::Cell(): row{0}, col{0} {}

bool Cell::getState() const { return isFilled; }

int Cell::getRow() const { return row; }

int Cell::getCol() const { return col; }

int Cell::getHeadRow() const { return headCell[0]; }

int Cell::getHeadCol() const { return headCell[1]; }

void Cell::setFilled() { 
  isFilled = true;
  notifyAllObservers();
}

void Cell::setUnfilled() {
  isFilled = false;
  notifyAllObservers();
}

void Cell::setCoords(int r, int c) { row = r; col = c; }

void Cell::setHead(int r, int c) { headCell[0] = r; headCell[1] = c; }

void Cell::setType(BlockType b) { type = b; }

int Cell::cellsLeft() { return block.size(); };

void Cell::attach(Observer *o) { observers.emplace_back(o); }

void Cell::detach(Observer *o) { 
  vector<Observer*>::iterator it = block.begin();
  bool found = false;
  int len = observers.size();
  for (int i = 0; i < len; ++i) {
    if (o == *it) { 
      found = true; 
      break; 
    } else {
      ++it;
    }
  }
  if (found && it != observers.end()) {
    cout << "found" << endl;
    observers.erase(it);
  }
}

void Cell::attachBlock(Observer *o) { block.emplace_back(o); }

void Cell::detachBlock(Observer *o) { 
  vector<Observer*>::iterator it = block.begin();
  bool found = false;
  int len = block.size();
  for (int i = 0; i < len; ++i) {
    if (o == *it) { 
      found = true; 
      break; 
    } else {
      ++it;
    }
  }
  if (found && it != block.end()) {
    block.erase(it);
  }
}


BlockType Cell::bType() { return type; }

CellType Cell::cType() { return CellType::InBlock; }

void Cell::notify(Cell &c) {
  isFilled = false;
  notifyAllObservers();
}

void Cell::notifyAllObservers() {
  for (auto o: observers) {
    if (o->cType() == CellType::All) {
      o->notify(*this);
    }
  }
}
