#ifndef JBLOCK__
#define JBLOCK__
#include <iostream>
#include "block.h"



struct JBlock : public Block
{
  static const char blockType = 'J';
 public:
  char getType() const;
  JBlock(int left, int down, int level, bool skip);
};

#endif
