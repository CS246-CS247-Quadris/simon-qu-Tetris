#include "block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "TBlock.h"
#include "ZBlock.h"
#include "level.h"
#include "leveltwo.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

LevelTwo::LevelTwo(bool skippable, bool extralevels)
: Level(skippable, extralevels)
{
}

Block* LevelTwo::getBlock()
{
  int level;
  // determining the level (based on whether bonus mode is on for levels)
  if (extralevels)
  {
    level = 2;
  }
  else
  {
    level = 1;
  }

  int random = 0;
  bool skip = false;
  if(skippable)
  {
    random = (rand() % 4) + 1;
    if(random == 1)
      skip = true;
  }
  random = (rand() % 12) + 1;
  switch(random)//IJLOSTZ
      {
        case 1:
          return new SBlock(0, 3, level, skip);
        case 2:
          return new ZBlock(0, 3, level, skip);
	 case 3:
	 case 4:
          return new IBlock(0, 3, level, skip);
        case 5:
	 case 6:
          return new JBlock(0, 3, level, skip);
        case 7:
	 case 8:
          return new LBlock(0, 3, level, skip);
        case 9:
	 case 10:
          return new OBlock(0, 3, level, skip);
        case 11:
	 case 12:
          return new TBlock(0, 3, level, skip);
      }
  return NULL;
}
