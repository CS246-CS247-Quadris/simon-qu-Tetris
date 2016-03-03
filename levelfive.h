#ifndef LEVELFIVE__
#define LEVELFIVE__
#include <iostream>
#include "block.h"
#include "level.h"

class LevelFive: public Level
{
 public:
  LevelFive(bool skippable, bool extralevels);
  Block* getBlock();
};

#endif
