#include "block.h"
#include "LBlock.h"
#include <iostream>



LBlock::LBlock(int left, int down, int level, bool skip) : Block(left, down, level, skip)
{
  //block-specific fields
  isTransposed = false;
  blockRows = 2;
  blockCols = 3;

  states = new bool*[blockRows];
  for(int i = 0; i < blockRows; i++)
    states[i] = new bool[blockCols];

  statesTransposed = new bool*[blockCols];
  for(int i = 0; i < blockCols; i++)
    statesTransposed[i] = new bool[blockRows];

  states[0][0] = false;
  states[0][1] = false;
  states[0][2] = true;
  states[1][0] = true;
  states[1][1] = true;
  states[1][2] = true;

 
}
  
  

char LBlock::getType() const
{
  return LBlock::blockType;
}


