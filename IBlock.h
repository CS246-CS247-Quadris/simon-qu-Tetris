#ifndef IBLOCK__
#define IBLOCK__
#include <iostream>
#include "block.h"



struct IBlock : public Block
{
  static const char blockType = 'I';
 public:
  char getType() const;
  IBlock(int left, int down, int level, bool skip);
};

#endif
