#include <iostream>
#include "block.h"
#include "boarddisplay.h"
#include "window.h"
using namespace std;

const int NUM_ROWS = 15;
const int NUM_COLS = 10;
const int WINDOW_HEIGHT = 500;
const int SQUARE_SIZE = (WINDOW_HEIGHT - 50) / NUM_ROWS;

// constructor
BoardDisplay::BoardDisplay(Xwindow* w)
{
  window = w;
  // initially everything's empty
  for (int i = 0; i < NUM_ROWS; i++) 
  {
    for (int j = 0; j < NUM_COLS; j++)
    {
      oldTheDisplay[i][j] = ' ';
    }
  }
}

void BoardDisplay::notify(int left, int down, int xState[], int yState[], char ch) //updates curBlock
{
  for(int i = 0; i < 4; i++)
  {
    int newY = down + yState[i];
    int newX = left + xState[i];
    theDisplay[newY][newX] = ch;
  }
}

void BoardDisplay::notify(Block*** grid) //from board.cc - updates entire board
{
  for(int i = 0; i< NUM_ROWS; i++)
  {
    for(int j = 0; j < NUM_COLS; j++)
    {
      if(grid[i][j] != NULL)
        theDisplay[i][j] = grid[i][j]->getType();
      else
        theDisplay[i][j] = ' ';
    }
  }
}

// prints the current board to out
ostream& operator<<(ostream& out, BoardDisplay& bd)
{
  for(int i = 0; i< NUM_ROWS; i++)
  {
    for(int j = 0; j < NUM_COLS; j++)
    {
      out << bd.theDisplay[i][j];
    }
    out << endl;
  }
  
  return out;
}

// draws the current board to the graphical display
void BoardDisplay::draw()
{
  for(int i = 0; i< NUM_ROWS; i++)
  {
    for(int j = 0; j < NUM_COLS; j++)
    {
      Block::drawBlock(window, oldTheDisplay[i][j], theDisplay[i][j], j*SQUARE_SIZE, i*SQUARE_SIZE, true);  
      oldTheDisplay[i][j] = theDisplay[i][j]; 
    }
  }
}
