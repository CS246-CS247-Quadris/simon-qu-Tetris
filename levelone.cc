#include "block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "TBlock.h"
#include "ZBlock.h"
#include "level.h"
#include "levelone.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

LevelOne::LevelOne(bool skippable, bool extralevels)
: Level(skippable, extralevels)
{
}

Block* LevelOne::getBlock()
{
  int random = 0;
  bool skip = false;
  if(skippable)
  {
    random = (rand() % 3) + 1;
    if(random == 1)
      skip = true;
  }

  random = (rand() % 5) + 1;
  switch(random)//no S or Z block generated, the rest equal probability
      {
	case 1:
          return new IBlock(0, 3, 1, skip);
        case 2:
          return new JBlock(0, 3, 1, skip);
        case 3:
          return new LBlock(0, 3, 1, skip);
        case 4:
          return new OBlock(0, 3, 1, skip);
	case 5:
          return new TBlock(0, 3, 1, skip);
      }
  return NULL;
}
