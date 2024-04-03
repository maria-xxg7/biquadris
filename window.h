#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s, width, height;
  GC gc;
  unsigned long colours[21];

 public:
  Xwindow(int width=388, int height=736);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Coral, DCoral, DarkGreen, DDarkGreen, LightGreen, DLightGreen, 
        SkyBlue, DSkyBlue, Purple, DPurple, Orange, DOrange, Yellow, DYellow,
        DarkestBlue, DarkBlue, Blue, LightBlue, Brown}; // Available colours.

  int getWidth() const;
  int getHeight() const;

  void drawRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg, int colour=Black);

};

#endif
