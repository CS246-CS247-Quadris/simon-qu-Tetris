#ifndef __BOARDDISPLAY__H
#define __BOARDDISPLAY__H
#include <iostream>
#include "window.h"

class Block;

class BoardDisplay
{
  char oldTheDisplay[15][10];
  char theDisplay[15][10];
  Xwindow* window;

 public:
  BoardDisplay(Xwindow* w); 
  void notify(int left, int down, int xState[], int yState[], char ch); //from block.cc
  void notify(Block*** grid); //from board.cc
  void draw();
  friend std::ostream& operator<<(std::ostream& out, BoardDisplay& bd);
};

#endif
