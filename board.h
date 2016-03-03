#ifndef BOARDH__
#define BOARDH__
#include "block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "TBlock.h"
#include "ZBlock.h"
#include "level.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include <iostream>
#include "boarddisplay.h"
#include <string>
#include "window.h"

class Board
{
  Level* levelType;
  Block* curBlock;
  Block* nextBlock;
  Block* holdBlock;
  Block*** grid;
  bool isGameOver;
  int score;
  int hiScore;
  BoardDisplay* bd;
  int levelNumber;

  bool validBlock(Block* block);
  void checkLines();
  void deallocHeap();
  void newAllocHeap();

  int startLevel;
  std::string fileName;
  Xwindow* window;

  int prevScore;
  int prevHiScore;
  int prevLevel;
  char prevBlock;
  bool prevHoldSkip;
  bool prevNextSkip;
  std::string prevMessage;

  bool fileExist;
  bool skippable;
  std::string message;//prints out informative error messages (invalid right move ... etc)
  char prevHold;
  std::string levelLine;
  std::string hiScoreLine;
  std::string scoreLine;
  bool holdable;
  bool extralevels;
  Level* createLevel();
 public:
  Board(std::string filename, int startingLevel, bool graphics, bool skip, bool hold, bool extralevels);
  ~Board();
  void notifyObserver();
  void left();
  void right();
  void down();
  void drop();
  void rotateCCW();
  void rotateCW();
  void levelUp();
  void levelDown();
  void restart();
  bool isTheGameOver();
  bool fileExists();
  void hold();
  void skip();
  void draw();
  friend std::ostream& operator<<(std::ostream& out, Board& b);
};


#endif


