#include "block.h"
#include "boarddisplay.h"
#include <iostream>
#include <string>
using namespace std;
const int NUM_ROWS = 15;
const int NUM_COLS = 10;
const int WINDOW_HEIGHT = 500;
const int SQUARE_SIZE = (WINDOW_HEIGHT - 50) / NUM_ROWS;

// a constructor for the superclass
Block::Block(int left, int down, int level, bool skip): 
  leftmost(left), downmost(down), levelCreated(level), squaresDeleted(0), beenHeld(false),
  isSkippable(skip)
{
}

// sets the window field
void Block::setWindow(Xwindow *window)
{
  this->window = window;
}

// notifies the TextDisplay of changes in positions of the block
void Block::notifyObserver(bool erasing) // true if purpose is to erase
                                         // false if purpose is to draw                                     
{
  char ch = erasing ? ' ' : getType();
  int* xStates = getXState();
  int* yStates = getYState();

  bd->notify(leftmost, downmost, xStates, yStates, ch);
  delete[] xStates;
  delete[] yStates;
}

// moves the block to the left
void Block::left()
{
  leftmost -= 1;
}

// moves the block to the right
void Block::right()
{
  leftmost += 1;
}

// moves the block down
void Block::down()
{
  downmost += 1;
}

// moves the block up
void Block::up() 
{
  downmost -= 1;
}

// returns the level the game was in when the block was generated
int Block::getLevel()
{
  return levelCreated;
}

// increments the number of times a square of the block has been cleared
void Block::deletePart()
{
  squaresDeleted += 1;
}  

// returns the number of times a square has been cleared 
int Block::getDeleted() 
{
  return squaresDeleted;
}

// returns the left most column coordinate
int Block::getLeftmost() 
{
  return leftmost;
}

// returns the down most row coordinate
int Block::getDownmost() 
{
  return downmost;
}

// attaches observer
void Block::attachObserver(BoardDisplay* bd)
{
  this->bd = bd;
}


// rotate clockwise
void Block::rotateCW() 
{
  if(!isTransposed) // horizontal before method call
  {
    for(int i = 0; i < blockRows; i++)
      for(int j = 0; j < blockCols; j++)
      {
        statesTransposed[j][(blockRows-1) - i] = states[i][j];
      }
  }
  else // vertical before method call
  {
    for(int i = 0; i < blockCols; i++)
      for(int j = 0; j < blockRows; j++)
      {
        states[j][(blockCols-1) - i] = statesTransposed[i][j];
      }
  }
  isTransposed = !isTransposed;
}


// rotate counterclockwise
void Block::rotateCCW() 
{ //rotates 3 times to simulate one CCW rotation
  rotateCW();
  rotateCW();
  rotateCW();
}

// returns the positions of the column coordinates
// relative to the bottom left coordinate
int* Block::getXState() 
{
  int* colState = new int[4];
  int numStored = 0;
  if(!isTransposed) // horizontal block
  {
    for(int i = 0; i < blockRows; i++)
      for(int j = 0; j < blockCols; j++)
        if(states[i][j])
        {
          colState[numStored] = j;
          numStored++;
        }
  }
  else // vertical block
  {
    for(int i = 0; i < blockCols; i++)
      for(int j = 0; j < blockRows; j++)
        if(statesTransposed[i][j])
        {
          colState[numStored] = j;
          numStored++;
        }
  }
  return colState;
}

// returns the positions of the row coordinates
// relative to the bottom left coordinate
int* Block::getYState()
{
  int* rowState = new int[4];
  int numStored = 0;
  if(!isTransposed) // horizonal block
  {
    for(int i = 0; i < blockRows; i++)
      for(int j = 0; j < blockCols; j++)
        if(states[i][j])
        {
          rowState[numStored] = i-(blockRows-1);
          numStored++;
        }
  }
  else // vertical block
  {
    for(int i = 0; i < blockCols; i++)
      for(int j = 0; j < blockRows; j++)
        if(statesTransposed[i][j])
        {
          rowState[numStored] = i-(blockCols-1);
          numStored++;
        }
  }
  return rowState;
}


// prints the block to out
ostream& operator<<(ostream& out, const Block* bl)
{
  for(int i = 0; i < bl->blockRows; i++)
  {
    for(int j = 0; j < bl->blockCols; j++)
    {
      if(bl->states[i][j])
	out << bl->getType();
      else
        out << ' ';
    }
    out << endl;
  }
  return out;
}

// deallocates the block object
Block::~Block()
{
  for(int i = 0; i < blockRows; i++)
  {
      delete[] states[i];
  }
 
 
  delete[] states;

  for(int i = 0; i < blockCols; i++)
  {
      delete[] statesTransposed[i];
  }
  delete[] statesTransposed;

}

// resets the block to be held
void Block::resetPosition()
{
  leftmost = 0;
  downmost = 3;
  if(isTransposed)
  {
    rotateCW();
  }
  beenHeld = true;
}

// returns whether a block is held
bool Block::hasBeenHeld()
{
  return beenHeld;
}

// returns whether the block is skippable
bool Block::getSkippable()
{
  return isSkippable;
}

// draws the square representing newchar to window
void Block::drawBlock(Xwindow *window, char oldchar, char newchar, int x, int y, bool checkRepeat)
{
    if (window != NULL && !(checkRepeat && oldchar == newchar)) 
      {
        // determining the colour of the box
        int colour[4];
	 if(newchar == ' ')
        {
	   colour[0]=0;
	   colour[1]=0;
	   colour[2]=0;
	   colour[3]=0;
        }
	 else if(newchar == 'I')
        {
	   colour[0]=5;
	   colour[1]=9;
	   colour[2]=10;
	   colour[3]=11;
        }
	 else if(newchar == 'J')
        {
	   colour[0]=4;
	   colour[1]=12;
	   colour[2]=13;
	   colour[3]=14;
        }
	 else if(newchar == 'L')
        {
	   colour[0]=8;
	   colour[1]=15;
	   colour[2]=16;
	   colour[3]=17;
        }
	 else if(newchar == 'O')
        {
	   colour[0]=6;
	   colour[1]=18;
	   colour[2]=19;
	   colour[3]=20;
        }
	 else if(newchar == 'S')
        {
	   colour[0]=3;
	   colour[1]=21;
	   colour[2]=22;
	   colour[3]=23;
        }
	 else if(newchar == 'T')
        {
	   colour[0]=7;
	   colour[1]=24;
	   colour[2]=25;
	   colour[3]=26;
        }
	 else if(newchar == 'Z')
        {
	   colour[0]=2;
	   colour[1]=27;
	   colour[2]=28;
	   colour[3]=29;
        }

        window->fillRectangle(x + 8, y + 38, SQUARE_SIZE-8,
                                SQUARE_SIZE-8, colour[0]); 
        int xPts[4];
  	 int yPts[4];
	 xPts[0] = x + 4;
	 xPts[1] = x + 4 + 4;
	 xPts[2] = x - 4 + SQUARE_SIZE + 4;
	 xPts[3] = x + SQUARE_SIZE + 4;
 	 yPts[0] = y + 34;
	 yPts[1] = y + 4 + 34;
	 yPts[2] = y + 4 + 34;
	 yPts[3] = y + 34;
        window->fillPolygon(xPts, yPts, 4, colour[1]); 
/////sides
	 xPts[0] = x + 4;
	 xPts[1] = x + 4 + 4;
	 xPts[2] = x + 4 + 4;
	 xPts[3] = x + 4;
 	 yPts[0] = y + 34;
	 yPts[1] = y + 4 + 34;
	 yPts[2] = y - 4 + SQUARE_SIZE + 34;
	 yPts[3] = y + SQUARE_SIZE + 34;
        window->fillPolygon(xPts, yPts, 4, colour[3]); 
	 xPts[0] = x + SQUARE_SIZE + 4;
	 xPts[1] = x - 4 + SQUARE_SIZE + 4;
	 xPts[2] = x - 4 + SQUARE_SIZE + 4;
	 xPts[3] = x + SQUARE_SIZE + 4;
 	 yPts[0] = y + 34;
	 yPts[1] = y + 4 + 34;
	 yPts[2] = y - 4 + SQUARE_SIZE + 34;
	 yPts[3] = y + SQUARE_SIZE + 34;
        window->fillPolygon(xPts, yPts, 4, colour[3]); 
//bottom
	 xPts[0] = x + 4;
	 xPts[1] = x + 4 + 4;
	 xPts[2] = x - 4 + SQUARE_SIZE + 4;
	 xPts[3] = x + SQUARE_SIZE + 4;
 	 yPts[0] = y + SQUARE_SIZE + 34;
	 yPts[1] = y - 4 + SQUARE_SIZE + 34;
	 yPts[2] = y - 4 + SQUARE_SIZE + 34;
	 yPts[3] = y + SQUARE_SIZE + 34;
        window->fillPolygon(xPts, yPts, 4, colour[2]); 

   }
}

// draws a block to the graphical display 
// used the draw the next and hold blocks
void Block::draw(int x, int y)
{
    for(int i = 0; i < blockRows; i++)
    {
      for(int j = 0; j < blockCols; j++)
      {
        if(states[i][j])
   	  drawBlock(window, getType(), getType(), x + j*SQUARE_SIZE, y + i*SQUARE_SIZE, false);
      }
    }
}
