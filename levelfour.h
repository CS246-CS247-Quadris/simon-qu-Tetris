#ifndef LEVELFOUR__
#define LEVELFOUR__
#include <iostream>
#include "block.h"
#include "level.h"

class LevelFour: public Level
{
 public:
  LevelFour(bool skippable, bool extralevels);
  Block* getBlock();
};

#endif
