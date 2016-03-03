#ifndef SBLOCK__
#define SBLOCK__
#include <iostream>
#include "block.h"



struct SBlock : public Block
{
  static const char blockType = 'S';
 public:
  char getType() const;
  SBlock(int left, int down, int level, bool skip);
};

#endif
