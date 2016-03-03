#include "block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "TBlock.h"
#include "ZBlock.h"
#include "level.h"
#include "levelthree.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

LevelThree::LevelThree(bool skippable, bool extralevels)
: Level(skippable, extralevels)
{
}

Block* LevelThree::getBlock()
{
  int levels;
  if (extralevels)
  {
    levels = 3;
  }
  else
  {
    levels = 2;
  }
  int random = 0;
  bool skip = false;
  if(skippable)
  {
    random = (rand() % 5) + 1;
    if(random == 1)
      skip = true;
  }
  random = (rand() % 7) + 1;
  switch(random)//IJLOSTZ
      {
        case 1:
          return new SBlock(0, 3, levels, skip);
        case 2:
          return new ZBlock(0, 3, levels, skip);
	 case 3:
          return new IBlock(0, 3, levels, skip);
	 case 4:
          return new JBlock(0, 3, levels, skip);
	 case 5:
          return new LBlock(0, 3, levels, skip);
	 case 6:
          return new OBlock(0, 3, levels, skip);
	 case 7:
          return new TBlock(0, 3, levels, skip);
      }
  return NULL;
}
