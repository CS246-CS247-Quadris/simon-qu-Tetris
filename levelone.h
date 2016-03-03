#ifndef LEVELONE__
#define LEVELONE__
#include <iostream>
#include "block.h"
#include "level.h"

class LevelOne: public Level
{
 public:
  LevelOne(bool skippable, bool extralevels);
  Block* getBlock();
};

#endif
