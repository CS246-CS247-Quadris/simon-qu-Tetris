#include "block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "TBlock.h"
#include "ZBlock.h"
#include "level.h"
#include "levelfour.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

LevelFour::LevelFour(bool skippable, bool extralevels)
: Level(skippable, extralevels)
{
}

Block* LevelFour::getBlock()
{
  int levels;
  if (extralevels)
  {
    levels = 4;
  }
  else
  {
    levels = 3;
  }
  int random = 0;
  bool skip = false;
  if(skippable)
  {
    random = (rand() % 5) + 1;
    if(random == 1)
      skip = true;
  }
  random = (rand() % 9) + 1;
  switch(random)//IJLOSTZ
      {
        case 1:
        case 2:
          return new SBlock(0, 3, levels, skip);
        case 3:
        case 4:
          return new ZBlock(0, 3, levels, skip);
	 case 5:
          return new IBlock(0, 3, levels, skip);
	 case 6:
          return new JBlock(0, 3, levels, skip);
	 case 7:
          return new LBlock(0, 3, levels, skip);
	 case 8:
          return new OBlock(0, 3, levels, skip);
	 case 9:
          return new TBlock(0, 3, levels, skip);
      }
  return NULL;
}
