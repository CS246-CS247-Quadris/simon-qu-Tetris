#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
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
  char color_vals[30][13]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange",
 			       "rgb:99/ff/ff", "rgb:00/72/72", "rgb:00/cc/cc", //cyans
				"rgb:8b/8b/ff", "rgb:00/00/54", "rgb:00/00/ab", //blues
				"rgb:ff/b7/6f", "rgb:76/3b/00", "rgb:d1/69/00", //oranges
				"rgb:ff/ff/75", "rgb:75/75/00", "rgb:da/c4/00", //yellows
				"rgb:6c/ff/6c", "rgb:00/62/00", "rgb:00/b7/00", //greens
				"rgb:ff/9c/ff", "rgb:58/00/58", "rgb:b9/00/b9", //magentas
				"rgb:ff/89/89", "rgb:6c/00/00", "rgb:d0/00/00"}; //reds
  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 30; ++i) {
      if (!XParseColor(d,cmap,color_vals[i],&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      if (!XAllocColor(d,cmap,&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
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
  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}
void Xwindow::drawRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XDrawRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}
void Xwindow::drawString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::fillPolygon(int x[], int y[], int npoints, int colour) {
//make xpoints array
  XPoint arr[npoints];
  for(int i = 0; i < npoints; i++)
  {
    arr[i].x = x[i];
    arr[i].y = y[i];
  }

  XSetForeground(d, gc, colours[colour]);
  XFillPolygon(d, w, gc, arr, npoints, Convex, CoordModeOrigin);
  XSetForeground(d, gc, colours[Black]);
}
