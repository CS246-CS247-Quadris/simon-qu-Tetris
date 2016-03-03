#ifndef LEVELTHREE__
#define LEVELTHREE__
#include <iostream>
#include "block.h"
#include "level.h"

class LevelThree: public Level
{
 public:
  LevelThree(bool skippable, bool extralevels);
  Block* getBlock();
};

#endif
