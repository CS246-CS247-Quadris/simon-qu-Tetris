#ifndef LEVELTWO__
#define LEVELTWO__
#include <iostream>
#include "block.h"
#include "level.h"

class LevelTwo: public Level
{
 public:
  LevelTwo(bool skippable, bool extralevels);
  Block* getBlock();
};

#endif
