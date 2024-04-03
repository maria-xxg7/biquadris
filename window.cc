#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) : width{width}, height{height} {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 5, 5, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;

  char color_vals[20][15]={"white", "black", "rgb:ff/82/8b", "rgb:be/5f/66",
    "rgb:70/a8/94", "rgb:9f/e7/93", "rgb:81/c4/de", "rgb:a8/8a/c2", 
    "rgb:ff/9f/73", "rgb:ff/df/87", "rgb:00/20/2e", "rgb:00/3f/5c",
    "rgb:2c/48/75", "rgb:d1/db/e4", "rgb:66/53/4c"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 20; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(5000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

int Xwindow::getWidth() const { return width; }
int Xwindow::getHeight() const { return height; }

void Xwindow::drawRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XDrawRectangle(d, w, gc, x, y, width, height);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
}

void Xwindow::drawString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
}



// #include <X11/Xlib.h>
// #include <X11/Xutil.h>
// #include <X11/Xos.h>
// #include <iostream>
// #include <cstdlib>
// #include <string>
// #include <unistd.h>
// #include "window.h"

// using namespace std;

// Xwindow::Xwindow(int width, int height) : width{width}, height{height} {

//   d = XOpenDisplay(NULL);
//   if (d == NULL) {
//     cerr << "Cannot open display" << endl;
//     exit(1);
//   }
//   s = DefaultScreen(d);
//   w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
//                           WhitePixel(d, s), WhitePixel(d, s));
//   XSelectInput(d, w, ExposureMask | KeyPressMask);
//   XMapRaised(d, w); 

//   Pixmap pix = XCreatePixmap(d,w,width,
//         height,DefaultDepth(d,DefaultScreen(d)));
//   gc = XCreateGC(d, pix, 0,(XGCValues *)0);

//   XFlush(d);
//   XFlush(d);

//   // Set up colours.
//   XColor xcolour;
//   Colormap cmap;
//   // char color_vals[12][15]={"white", "black", "gray", "dim gray", "rgb:ff/82/8b",
//   //   "rgb:70/a8/94", "rgb:9f/e7/93", "rgb:81/c4/de", "rgb:a8/8a/c2", 
//   //   "rgb:ff/df/87", "midnight blue"};
  
//   char color_vals[12][15]={"white", "black", "dim gray", "gray", "light coral", 
//     "blue"};

//   cmap=DefaultColormap(d,DefaultScreen(d));
//   for(int i=0; i < 5; ++i) {
//       XParseColor(d,cmap,color_vals[i],&xcolour);
//       XAllocColor(d,cmap,&xcolour);
//       colours[i]=xcolour.pixel;
//   }

//   XSetForeground(d,gc,colours[Black]);

//   // Make window non-resizeable.
//   XSizeHints hints;
//   hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
//   hints.height = hints.base_height = hints.min_height = hints.max_height = height;
//   hints.width = hints.base_width = hints.min_width = hints.max_width = width;
//   XSetNormalHints(d, w, &hints);

//   XSynchronize(d,True);

//   usleep(1000);
// }

// Xwindow::~Xwindow() {
//   XFreeGC(d, gc);
//   XCloseDisplay(d);
// }

// int Xwindow::getWidth() const { return width; }
// int Xwindow::getHeight() const { return height; }

// void Xwindow::drawRectangle(int x, int y, int width, int height, int colour) {
//   XSetForeground(d, gc, colours[colour]);
//   XDrawRectangle(d, w, gc, x, y, width, height);
// }

// void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
//   XSetForeground(d, gc, colours[colour]);
//   XFillRectangle(d, w, gc, x, y, width, height);
// }

// void Xwindow::drawString(int x, int y, string msg, int colour) {
//   XSetForeground(d, gc, colours[colour]);
//   XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
// }
 