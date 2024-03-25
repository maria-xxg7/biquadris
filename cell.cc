#include "cell.h"

Cell::Cell(): row{0}, col{0} {}

bool Cell::getState() const { return isFilled; }

int Cell::getRow() const { return row; }

int Cell::getCol() const { return col; }

void Cell::setFilled() { 
  isFilled = true;
  notifyRowObservers();
  notifyAllObservers();
}

void Cell::setCoords(int r, int c) { row = r; col = c; }

void Cell::setType(BlockType b) { type = b; }
void Cell::attach(Observer *o) {
  observers.emplace_back(o);
}

BlockType Cell::bType() {
  return type;
}

Row Cell::rowType() {
  return Row::inRow;
}

void Cell::notify(Cell &c) {
  isFilled = false;
  notifyAllObservers();
}

void Cell::notifyAllObservers() {
  for (auto o: observers) {
    if (o->rowType() == Row::All) {
      o->notify(*this);
    }
  }
}

void Cell::notifyRowObservers() {
  for (auto o: observers) {
    if (o->rowType() == Row::inRow) {
      o->notify(*this);
    }
  }
}
