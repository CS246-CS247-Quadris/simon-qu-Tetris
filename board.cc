#include "board.h"
#include "block.h"
#include "level.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "levelfive.h"
#include "boarddisplay.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include "window.h"
#include <sstream>
using namespace std;

// in the board, the first index represents the row number(y coordinate)
// and the second index represents the column number (x coordinate)
// the top left corner is 0 0 
// NULL is used to indicate unoccupied spots on the board
// the current block is not stored in the grid
const int NUM_ROWS = 15;
const int NUM_COLS = 10;
const int WINDOW_HEIGHT = 500;
const int SQUARE_SIZE = (WINDOW_HEIGHT - 50) / NUM_ROWS;
const int GRID_WIDTH = SQUARE_SIZE * NUM_COLS;

// the constructor for the board class
Board::Board(string filename, int startingLevel, bool graphics, bool skip, bool hold, bool extralevels)
: isGameOver(false),score(0), hiScore(0), levelNumber(startingLevel), 
  startLevel(startingLevel), fileName(filename), prevScore(-1), 
  prevHiScore(-1), prevLevel(-1), prevBlock(' '), prevHoldSkip(false),
  prevNextSkip(false), prevMessage(""), skippable(skip), message(""), prevHold(' '),
  levelLine(""), hiScoreLine(""), scoreLine(""), holdable(hold),
  extralevels(extralevels)

{
  fileExist = LevelZero::setFileSource(filename);
  window = NULL;

  if (fileExist && graphics)
  {
    window = new Xwindow(WINDOW_HEIGHT + 100, WINDOW_HEIGHT);
    window->fillRectangle(GRID_WIDTH+6, 15, 2, WINDOW_HEIGHT - 27, 1);
    window->fillRectangle(0, 15, 2, WINDOW_HEIGHT - 29, 1);
    window->fillRectangle(0, 15, GRID_WIDTH+6, 2, 1);
    window->fillRectangle(0, WINDOW_HEIGHT - 14, GRID_WIDTH+6, 2, 1);
    window->drawString(313, 490, "Quadris, by Siming Qi, Xinpeng Zhao (CS246_051)");
    window->drawRectangle(379, 220, 175, 85, 1); //block container
    window->drawRectangle(379, 30, 130, 150, 1); //score container
    window->drawString(385, 210, "Next:");
    if(holdable)
    {
      window->drawString(385, 320, "Hold:");
      window->drawRectangle(379, 330, 175, 85, 1); //hold container
    }
  }
  
  if (fileExist)
  {
    newAllocHeap();
  }
} 

//
void Board::notifyObserver() //bd->notify must be able to distinguish a board call
   				 //from a block call. Overload the notify method.                               
{
  bd->notify(grid);
}


// a private method that returns whether the positions
// of the current block would be valid 
bool Board::validBlock(Block* block) 
{
  int left = block->getLeftmost();
  int down = block->getDownmost();
  int* relXCoords = block->getXState();
  int* relYCoords = block->getYState();
  bool valid = true;
  for (int i = 0; i < 4 && valid; i++)
  {
    int newY = down + relYCoords[i];
    int newX = left + relXCoords[i];
    // checking for out of boundary 
    if (newY < 0 || newY >= NUM_ROWS) 
    {
      valid = false;
    }
    else if (newX < 0 || newX >= NUM_COLS) 
    {
      valid = false;
    }
    // checking for overlapping with existing blocks
    else if (grid[newY][newX] != NULL)
    {
      valid = false;
    }
  }
  delete[] relXCoords;
  delete[] relYCoords;
  return valid;
}

// move the current block to the left
// copy to right down cw ccw
void Board::left()
{ 
  curBlock->notifyObserver(true); // erase
  curBlock->left();
  if (!validBlock(curBlock)) // move back if invalid
  {
    curBlock->right();
  }
  curBlock->notifyObserver(false); // draw
}

// move the current block to the right
void Board::right()
{ 
  curBlock->notifyObserver(true);
  curBlock->right();
  if (!validBlock(curBlock)) // move back if invalid
  {
    curBlock->left();
  }
  curBlock->notifyObserver(false);
}

// move the current block downward
void Board::down()
{ 
  curBlock->notifyObserver(true);
  curBlock->down();
  if (!validBlock(curBlock)) // move back if invalid
  {
    curBlock->up();
  }
  curBlock->notifyObserver(false);
}

// rotate the current block clockwise
void Board::rotateCW()
{ 
  curBlock->notifyObserver(true);
  curBlock->rotateCW();
  if (!validBlock(curBlock)) // move back if invalid
  {
    curBlock->rotateCCW();
  }
  curBlock->notifyObserver(false);
}

// rotate the current block counterclockwise
void Board::rotateCCW()
{ 
  curBlock->notifyObserver(true);
  curBlock->rotateCCW();
  if (!validBlock(curBlock)) // move back if invalid
  {
    curBlock->rotateCW();
  }
  curBlock->notifyObserver(false);
}

Level* Board::createLevel()
{
  if (extralevels)
  {
    switch (levelNumber)
    {
      case 0: return new LevelZero(skippable, extralevels);
      case 1: return new LevelOne(skippable, extralevels);
      case 2: return new LevelTwo(skippable, extralevels);
      case 3: return new LevelThree(skippable, extralevels);
      case 4: return new LevelFour(skippable, extralevels);
      case 5: return new LevelFive(skippable, extralevels);
    }
  }
  else
  {
    switch (levelNumber)
    {
      case 0: return new LevelZero(skippable, extralevels);
      case 1: return new LevelTwo(skippable, extralevels);
      case 2: return new LevelThree(skippable, extralevels);
      case 3: return new LevelFour(skippable, extralevels);
    }
  }
  return NULL;
}

// increases the level by 1
void Board::levelUp()
{
  int maxLevel;
  if (extralevels)
  {
    maxLevel = 5;
  }
  else
  {
    maxLevel = 3;
  }

  if (levelNumber < maxLevel) 
  {
    levelNumber += 1;
  }
  delete levelType;
   
  levelType = createLevel();
}

// decreases the level by 1 
void Board::levelDown()
{
  if (levelNumber > 0)
  {
    levelNumber -= 1;
  }
  delete levelType;
  levelType = createLevel();
}

//make private
//checks if line is filled
//then removes if it is
void Board::checkLines()
{
  int numLinesCleared = 0;
  for(int i = 0; i < NUM_ROWS; i++)
  {
    bool lineFilled = true;
    for(int j = 0; j < NUM_COLS; j++)
    {
      if(grid[i][j] == NULL) 
      {
        lineFilled = false;
      }
    }

    if(lineFilled)//remove process
    {
      numLinesCleared++;
      for(int j = 0; j < NUM_COLS; j++) //record delete parts
      {
        grid[i][j]->deletePart();
        if(grid[i][j]->getDeleted() >= 4)
	 {
	   score += (1 + grid[i][j]->getLevel()) * (1 + grid[i][j]->getLevel());
          if(score > hiScore)
            hiScore = score;
	   delete grid[i][j]; //dealloc and record score
	 } 
	grid[i][j] = NULL; //set the line to null
      }
      delete[] grid[i]; //deletes the line array
      for(int k = i; k > 0; k--) //and shifts everything down
      {
        grid[k] = grid[k-1];
      }
      grid[0] = new Block* [NUM_COLS]; //and replaces the top line
      for (int k = 0; k < NUM_COLS; k++)
      {
        grid[0][k] = NULL;
      }
    }
  }

  if(numLinesCleared > 0)
  {
    score += (levelNumber + numLinesCleared) * (levelNumber + numLinesCleared);
    if(score > hiScore)
      hiScore = score;
  }
}

// drops the current block 
void Board::drop()
{
  curBlock->notifyObserver(true);
  curBlock->down();
  while(validBlock(curBlock))
  {
    curBlock->down();
  }
  curBlock->up();
  //curBlock is placed onto the textDisplay by board instead.

  //stores current block permanently.
  int left = curBlock->getLeftmost();
  int down = curBlock->getDownmost();
  int* relXCoords = curBlock->getXState();
  int* relYCoords = curBlock->getYState(); 

  for(int i = 0; i < 4; i++)
  {
    grid[down + relYCoords[i]][left + relXCoords[i]] = curBlock;    
  }
  delete[] relXCoords;
  delete[] relYCoords;

  //switches to the next block
  curBlock = nextBlock;

  //check for line clear
  //check for block clear
  checkLines();

  //generates new block
  nextBlock = levelType->getBlock();
  nextBlock->attachObserver(bd);
  nextBlock->setWindow(window);
  notifyObserver();

  //check for valid starting position. If not, game over.
  if(validBlock(curBlock))
    curBlock->notifyObserver(false);
  else
  {
    isGameOver = true;
  }
 
}  

void Board::deallocHeap() //deallocates everything heap-allocated
{
  for(int i=0; i < NUM_ROWS; i++)
  {
    for(int j=0; j< NUM_COLS; j++)
    {
      if(grid[i][j] != NULL)
      {
        grid[i][j]->deletePart();
        if(grid[i][j]->getDeleted() >= 4)
        {
          delete grid[i][j]; //deallocs the cell object
        }
      }
    }
    delete[] grid[i];
  }
  delete[] grid;

  delete levelType;
  delete curBlock;
  delete nextBlock;
  delete holdBlock;
  delete bd;
}

// allocates the heap based memory
void Board::newAllocHeap()
{
  levelType = createLevel();
  curBlock = levelType->getBlock();
  nextBlock = levelType->getBlock();
  curBlock->setWindow(window);
  nextBlock->setWindow(window);
  bd = new BoardDisplay(window);
  curBlock->attachObserver(bd);
  nextBlock->attachObserver(bd);
  holdBlock = NULL;
  grid = new Block** [NUM_ROWS];
  for(int i = 0; i< NUM_ROWS; i++)
  {
    grid[i] = new Block* [NUM_COLS];
    for(int j = 0; j < NUM_COLS; j++)
    {
      grid[i][j] = NULL;
    }
  }
  notifyObserver();
  curBlock->notifyObserver(false);
} 

// resets the game
void Board::restart()
{
  if (window != NULL)
  {
    window->fillRectangle(2, 17, GRID_WIDTH + 4, WINDOW_HEIGHT - 31, 0);
    window->fillRectangle(380, 331, 174, 84, 0);
    window->fillRectangle(440, 310, 108, 12, 0); //clears holdblock status
  }
  isGameOver = false;
  levelNumber = startLevel;
  prevHold = ' ';

  LevelZero::closeFile();
  LevelZero::setFileSource(fileName);
  if (score > hiScore) 
  {
    hiScore = score;
  }
  score = 0;
  deallocHeap();
  newAllocHeap();
  message = "";
}


// destructor for the class
Board::~Board()
{
  if (fileExist)
  {
    deallocHeap();
  }
  if (fileExist && window != NULL)
  {
    delete window;
  }
}


bool Board::isTheGameOver()
{
  return isGameOver; //accessor for mainline function to stop taking commands
}

// prints the game board to out
ostream& operator<<(ostream& out, Board& b)
{
  if (b.isTheGameOver())
  {
    cout << "Game over!" << endl;
  }
  b.levelLine = "";
  b.hiScoreLine = "";
  b.scoreLine = "";
  int hiscoreLength = 1;
  int hi = b.hiScore;
  // if theres at least 1 digit left, add 1 to length, and remove the digit
  while(hi/10 != 0)
  { 
    hi /= 10;
    hiscoreLength++;
  }

  int scoreLength = 1;
  int sc = b.score;
  // if theres at least 1 digit left, add 1 to length, and remove the digit
  while(sc/10 != 0)
  { 
    sc /= 10;
    scoreLength++;
  }

  b.levelLine = "Level:    "; // printed in the window
  //prints the level line
  out << "Level:    ";
  for(int i = 0; i < hiscoreLength - 1; i++)
  {
    out << " ";
    b.levelLine += " ";
  }
  out << b.levelNumber << endl;
  stringstream levelStr;
  levelStr << b.levelNumber;
  b.levelLine += levelStr.str();
  
  b.scoreLine =  "Score:    ";
  //prints the score line
  out << "Score:    ";
  for(int i = 0; i < hiscoreLength - scoreLength; i++)
  {
    out << " ";
    b.scoreLine += " ";
  }
  out << b.score << endl;
  stringstream scoreStr;
  scoreStr << b.score;
  b.scoreLine += scoreStr.str();

  b.hiScoreLine = "Hi Score: ";
  //prints the hiscore line
  out << "Hi Score: " << b.hiScore << endl;
  stringstream hiScoreStr;
  hiScoreStr << b.hiScore;
  b.hiScoreLine += hiScoreStr.str();

  //prints the grid
  out << "----------" << endl;
  out << *(b.bd);                   //calls BoardDisplay's printer
  out << "----------";
  if (b.curBlock->getSkippable())
    out << "  CURRENT BLOCK IS SKIPPABLE";
  out << endl;
  

  //prints the next block
  out << "Next:";
  if (b.nextBlock->getSkippable())
    out << "  Skippable!";
  out << endl;
  out << b.nextBlock; //calls Block's printer
  if(b.holdable)
  {
    out << "Hold:";
    if (b.holdBlock != NULL && b.holdBlock->getSkippable())
      out << "  Skippable!";
    out << endl;
  
    if(b.holdBlock != NULL)
      out << b.holdBlock; //calls Block's printer
    else
      out << endl << endl;
  }
  return out;
}

// checks whether the file name exists
bool Board::fileExists()
{
  return fileExist;
}

// holds a block for later usage
void Board::hold()
{
  if(holdable && ((holdBlock == NULL) || (!curBlock->hasBeenHeld() && validBlock(holdBlock))))
  {
    curBlock->notifyObserver(true);
    curBlock->resetPosition();
    if(holdBlock == NULL) // no block is currently held
    {
      holdBlock = curBlock;
      curBlock = nextBlock;
      nextBlock = levelType->getBlock();
      nextBlock->setWindow(window);
      nextBlock->attachObserver(bd);
      curBlock->resetPosition();
    }
    else
    {
      Block* temp = holdBlock;
      holdBlock = curBlock;
      curBlock = temp;
    }//swaps the blocks
    curBlock->notifyObserver(false);

  }  
}

// skips the current block
void Board::skip()
{
  if(curBlock->getSkippable() && validBlock(nextBlock))
  {
    curBlock->notifyObserver(true);
    delete curBlock;
    curBlock = nextBlock;
    checkLines();

    //generates new block
    nextBlock = levelType->getBlock();
    nextBlock->setWindow(window);
    nextBlock->attachObserver(bd);
    notifyObserver();
    curBlock->notifyObserver(false);

  }
}

// draws the game board to the graphical display
void Board::draw()
{
  if(window == NULL)
    return;
  
  // updating window scoreboard and next block if necessary
  if (levelNumber != prevLevel) // level
  {
    window->fillRectangle(400, 40, 100, 10, 0);
    window->drawString(400, 50, levelLine);
    prevLevel = levelNumber;
  }
  if (score != prevScore)  // score
  {
    window->fillRectangle(400, 90, 108, 10, 0);
    window->drawString(400, 100, scoreLine);
    prevScore = score;
  }
  if (hiScore != prevHiScore) // hi score
  {
    window->fillRectangle(400, 140, 108, 10, 0);
    window->drawString(400, 150, hiScoreLine);
    prevHiScore = hiScore;
  }

  if (holdBlock != NULL && holdBlock->getSkippable() != prevHoldSkip) //alert skippability
  {
    if(holdBlock->getSkippable())
      window->drawString(440, 320, "Skippable!");
    else
      window->fillRectangle(440, 310, 108, 12, 0);
    prevHoldSkip = holdBlock->getSkippable();
  }
  if (curBlock->getSkippable()) ///alert skippability
  {
    message += "SKIP IS CURRENTLY POSSIBLE";
  }
  if (nextBlock->getSkippable() != prevNextSkip) //alert skippability
  {
    if(nextBlock->getSkippable())
      window->drawString(440, 210, "Skippable!");
    else
      window->fillRectangle(440, 200, 108, 12, 0);
    prevNextSkip = nextBlock->getSkippable();
  }
  if(message != prevMessage)
  {
    window->fillRectangle(340, 450, 300, 12, 0);
    window->drawString(340, 460, message);
  }
  prevMessage = message;
  message = "";

  if (nextBlock->getType() != prevBlock) // next block
  {
    window->fillRectangle(390, 221, 163, 84, 0);
    nextBlock->draw(400, 200);
    prevBlock = nextBlock->getType();
  }
  if(holdable && holdBlock != NULL && holdBlock->getType() != prevHold)
  {
    window->fillRectangle(390, 331, 163, 84, 0);
    holdBlock->draw(400,310);
    prevHold = holdBlock->getType();
  }
  bd->draw();
  if (isGameOver) // drawing message to window indicating game over
  {
    window->drawString(GRID_WIDTH / 2, WINDOW_HEIGHT / 2, "Game Over!");
  }
}
