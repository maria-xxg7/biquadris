#include <iostream>
#include "window.h"

using namespace std;

int main() {
  Xwindow w;
  // draw background
  w.drawString(50, 50, "Level", Xwindow::Coral);

  // draw board
  w.fillRectangle(58, 113, 385, 525, Xwindow::Black);

  // fill in board grid pattern
  for (int i = 58; i < 443; i+=35) {
    for (int j = 113; j < 638; j+=35) {
      w.drawRectangle(i, j, 35, 35, Xwindow::DarkGrey);
      // w.fillRectangle(i+1, j+1, 33, 33, Xwindow::Coral);
    }
  }


  char c;
  cin >> c;
  // window closes when destructor is run, so wait for a character to be input
}

