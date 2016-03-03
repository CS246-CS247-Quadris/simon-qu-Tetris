#ifndef BLOCK__
#define BLOCK__

#include <iostream>
#include <string>
#include "boarddisplay.h"

class Xwindow;
class Block 
{
  Xwindow *window;
  int leftmost;
  int downmost;
  BoardDisplay* bd;
  int levelCreated;
  int squaresDeleted;
  bool beenHeld;
  bool isSkippable;
 protected:

  bool **states; //rectangle enclosing the block
  bool **statesTransposed; //sideways rectangle enclosing the block (after rotation)
  bool isTransposed;
  int blockRows;
  int blockCols;
  Block(int left, int down, int level, bool skip);

 public:
  static void drawBlock(Xwindow *window, char oldchar, char newchar, int x, int y, bool checkRepeat);
  void setWindow(Xwindow *window);
  ~Block();
  virtual char getType() const = 0;
  void rotateCCW();
  void rotateCW();
  int* getXState();
  int* getYState();
  bool skippable();
  void notifyObserver(bool erasing);
  void up();
  void left();
  void right();
  void down(); 
  int getLevel();
  void deletePart();
  void attachObserver(BoardDisplay* bd);
  int getDeleted();
  int getLeftmost();
  int getDownmost();
  void resetPosition();
  bool hasBeenHeld();
  bool getSkippable();
  void draw(int x, int y);
  friend std::ostream& operator<<(std::ostream& out, const Block* bl);
};
 
#endif
