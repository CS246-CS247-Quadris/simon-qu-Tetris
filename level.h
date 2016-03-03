#ifndef LEVEL__
#define LEVEL__
#include <iostream>

class Block;

class Level
{
 protected:
  bool skippable;
  bool extralevels;
  Level(bool skip, bool extra);
 public:
  virtual Block* getBlock() = 0;
  ~Level();
};

#endif
