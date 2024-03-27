#include "cell.h"

Cell::Cell(): row{0}, col{0} {}

bool Cell::getState() const { return isFilled; }

int Cell::getRow() const { return row; }

int Cell::getCol() const { return col; }

void Cell::setFilled() { 
  isFilled = true;
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

RowType Cell::rType() {
  return RowType::inRow;
}


void Cell::notify(Cell &c) {
  isFilled = false;
  notifyAllObservers();
}

void Cell::notifyAllObservers() {
  for (auto o: observers) {
    if (o->rType() == RowType::All) {
      o->notify(*this);
    }
  }
}
