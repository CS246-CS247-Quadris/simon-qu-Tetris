#include "block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "TBlock.h"
#include "ZBlock.h"
#include "level.h"
#include "levelfive.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

LevelFive::LevelFive(bool skippable, bool extralevels)
: Level(skippable, extralevels)
{
}

Block* LevelFive::getBlock()
{
  int random = 0;
  bool skip = false;
  if(skippable)
  {
    random = (rand() % 4) + 1;
    if(random == 1)
      skip = true;
  }
  random = (rand() % 3) + 1;
  switch(random)// S or Z or T block generated
      {
	case 1:
          return new SBlock(0, 3, 5, skip);
        case 2:
          return new ZBlock(0, 3, 5, skip);
        case 3:
          return new TBlock(0, 3, 5, skip);
      }
  return NULL;
}
