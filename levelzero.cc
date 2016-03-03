#include "block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "TBlock.h"
#include "ZBlock.h"
#include "level.h"
#include "levelzero.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

ifstream LevelZero::file;
string LevelZero::filename;

// opens file - returns whether file was successfully opened
bool LevelZero::setFileSource(string name)
{
  filename = name;
  file.open(filename.c_str());
  if (!file.is_open()) // file doesn't exist -exit program
  {
    cerr << name << " file does not exist" << endl;
    return false;
  }
  else
  {
    bool empty = true; // contains no block characters
    while (empty)
    {
      char input;
      file >> input;
      if (file.eof()) break;
      if (input == 'I' || input == 'J' || input == 'L' || input == 'O'
          || input == 'S' || input == 'T' || input == 'Z')
      {
        empty = false;
      }
    }
    file.close();
    file.open(filename.c_str());
    if (empty) // file contains no blocks - exist program
    {
      cerr << name << " contains no blocks" << endl;
      return false;
    }
    return true;
  }
}

// closes file
void LevelZero::closeFile()
{
  file.close();
}

LevelZero::LevelZero(bool skippable, bool extralevels)
: Level(skippable, extralevels)
{
}

// returns a block from the file
Block* LevelZero::getBlock()
{
  char c = ' ';
  bool skip = false;
  if(skippable)
  {
    int random = 0;
    random = (rand() % 2) + 1;
    if(random == 1)
      skip = true;
  }
  while(true)
  {
    LevelZero::file >> c;
    if(LevelZero::file.eof()) //if end of file, goes back to beginning of file
    {
      LevelZero::file.close();
      LevelZero::file.open(filename.c_str());
      LevelZero::file >> c;
    }
    if(!isspace(c))
    {
      switch(c)//IJLOSTZ
      {
        case 'I':
          return new IBlock(0, 3, 0, skip);
        case 'J':
          return new JBlock(0, 3, 0, skip);
	 case 'L':
          return new LBlock(0, 3, 0, skip);
	 case 'O':
          return new OBlock(0, 3, 0, skip);
	 case 'S':
          return new SBlock(0, 3, 0, skip);
	 case 'T':
          return new TBlock(0, 3, 0, skip);
	 case 'Z':
          return new ZBlock(0, 3, 0, skip);
      }
    }
  }
  return NULL;
}
