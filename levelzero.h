#ifndef LEVELZERO__
#define LEVELZERO__
#include <iostream>
#include <fstream>
#include "block.h"
#include "level.h"
#include <string>

class LevelZero: public Level
{
  static std::ifstream file;
  static std::string filename;
 public:
  static bool setFileSource(std::string name);
  static void closeFile();
  LevelZero(bool skippable, bool extralevels);
  Block* getBlock();
};

#endif
