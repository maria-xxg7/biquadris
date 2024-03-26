#include <iostream>
#include "window.h"

using namespace std;

int main() {
  Xwindow w;

  w.fillRectangle(58, 113, 385, 525, Xwindow::Blue);

  w.drawString(50, 50, "Hello!");

  char c;
  cin >> c;
  // window closes when destructor is run, so wait for a character to be input
}

