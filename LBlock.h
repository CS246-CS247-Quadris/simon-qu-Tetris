#ifndef LBLOCK__
#define LBLOCK__
#include <iostream>
#include "block.h"



struct LBlock : public Block
{
  static const char blockType = 'L';
 public:
  char getType() const;
  LBlock(int left, int down, int level, bool skip);
};

#endif
