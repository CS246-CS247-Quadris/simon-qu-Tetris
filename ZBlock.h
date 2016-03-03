#ifndef ZBLOCK__
#define ZBLOCK__
#include <iostream>
#include "block.h"



struct ZBlock : public Block
{
  static const char blockType = 'Z';
 public:
  char getType() const;
  ZBlock(int left, int down, int level, bool skip);
};

#endif
