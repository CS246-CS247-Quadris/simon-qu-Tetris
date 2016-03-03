#ifndef OBLOCK__
#define OBLOCK__
#include <iostream>
#include "block.h"



struct OBlock : public Block
{
  static const char blockType = 'O';
 public:
  char getType() const;
  OBlock(int left, int down, int level, bool skip);
};

#endif
