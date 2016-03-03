#include "block.h"
#include "level.h"
#include <iostream>

Level::Level(bool skip, bool extra): skippable(skip), extralevels(extra)
{
}

Level::~Level()
{
}
