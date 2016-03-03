#include "block.h"
#include "JBlock.h"
#include <iostream>



JBlock::JBlock(int left, int down, int level, bool skip) : Block(left, down, level, skip)
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

  states[0][0] = true;
  states[1][0] = true;
  states[1][1] = true;
  states[1][2] = true;
  states[0][2] = false;
  states[0][1] = false;
 
}
  
  

char JBlock::getType() const
{
  return JBlock::blockType;
}


