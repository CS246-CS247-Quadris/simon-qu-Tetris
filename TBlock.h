#ifndef TBLOCK__
#define TBLOCK__
#include <iostream>
#include "block.h"



struct TBlock : public Block
{
  static const char blockType = 'T';
 public:
  char getType() const;
  TBlock(int left, int down, int level, bool skip);
};

#endif
