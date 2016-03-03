#include "block.h"
#include "IBlock.h"
#include <iostream>



IBlock::IBlock(int left, int down, int level, bool skip) : Block(left, down, level, skip)
{
  //block-specific fields
  isTransposed = false;
  blockRows = 1;
  blockCols = 4;

  states = new bool*[blockRows];
  for(int i = 0; i < blockRows; i++)
    states[i] = new bool[blockCols];

  statesTransposed = new bool*[blockCols];
  for(int i = 0; i < blockCols; i++)
    statesTransposed[i] = new bool[blockRows];

  states[0][0] = true;
  states[0][1] = true;
  states[0][2] = true;
  states[0][3] = true;
 
}
  
  

char IBlock::getType() const
{
  return IBlock::blockType;
}


