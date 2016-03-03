#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "board.h"
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) 
{
  const int NUM_COMMANDS = 12;
  string commands[NUM_COMMANDS] = {"left", "right", "down", "clockwise",
                                   "counterclockwise", "drop", "levelup",
                                   "leveldown", "restart", "hold", "rename", "skip"};
  string filename = "sequence.txt";
  bool hold = false;
  int startingLevel = 0;
  bool graphics = true;
  bool skip = false;
  bool rename = false;
  bool extralevels = false;
  // getting command line inputs 
  // text option and scriptfile need to be passed to appropriate classes
  for (int i = 0; i < argc; i++)
  {
    string command(argv[i]);
    if(command == "-text")
    {
      graphics = false;
    }
    else if (command == "-rename")
    {
      rename = true;
    }
    else if (command == "-extralevels")
    {
      extralevels = true;
    }
    else if(command == "-skip")
    {
      skip = true;
    }
    else if(command == "-hold")
    {
      hold = true;
    }
    else if(command == "-seed" && i + 1 < argc)
    {
      string next(argv[i + 1]);
      stringstream seedStr(next);
      int seed;
      seedStr >> seed;
      srand(seed);
    }
    else if(command == "-startlevel" && i + 1 < argc) 
    {
      string next(argv[i + 1]);
      stringstream levelStr(next);
      levelStr >> startingLevel;
    }
    else if(command == "-scriptfile" && i + 1 < argc)
    { 
      string next(argv[i + 1]);
      filename = next;
    }
  }
  Board board(filename, startingLevel, graphics, skip, hold, extralevels);
  if (!board.fileExists()) // exists program if file not found
  {
    return 0;
  }
  cout << board;
  board.draw();
  for ( ;; )
  {
    // getting input from user
    int times;
    cin >> times;
    if (cin.eof()) break;

    string input;
    if (cin.fail()) 
    {
      times = 1;
      cin.clear();
    }
    cin >> input;
    if (cin.eof()) break;

    // finding the index number of the command that matches the input
    int index = -1;
    for (int i = 0; i < NUM_COMMANDS && index == -1; i++)
    {
      // matches if current command starts with the input 
      // and all other command do not start with the input
      if (input == commands[i].substr(0, input.length()))
      {
        bool notMatching = true;
        for (int j = 0; j < NUM_COMMANDS && notMatching; j++)
        {
          if (i != j && input == commands[j].substr(0, input.length())) 
          {
            notMatching = false;
          }
        }
        
        if (notMatching) // index found
        {
          index = i;
        }
      }
    }

    if (index == 8 || index == 10) // multiplier is invalid to restart 
                                  // and rename command
    {
      times = 1;
    }

    for (int i = 0; i < times; i++)
    {
      if (board.isTheGameOver() && index != 8 && index != 10)
        index = -1;   //only allow restart commands when game is over.
      // taking appropriate action based on the index number matched
      switch (index) 
      {
        case 0: board.left();  
                break;
        case 1: board.right();
                break;
        case 2: board.down();
                break;
        case 3: board.rotateCW();
                break;
        case 4: board.rotateCCW();
                break;
        case 5: board.drop();
                break;
        case 6: board.levelUp();
                break;
        case 7: board.levelDown();
                break;
        case 8: board.restart();
                break;
        case 9: board.hold();
                break;
        case 11: board.skip();
                 break;     
        case 10: if (!rename) break;
                 bool found = false;    // rename command
                 string origCommand;
                 string newCommand;
                 cin >> origCommand;
                 cin >> newCommand;
                 for (int i = 0; i < NUM_COMMANDS && !found; i++)
                 {
                   if (commands[i] == origCommand)
                   {
                     found = true;
                     bool noOverlap = true; // if another command has same name                                            
                                          // as changed name, no changes occur
                     for (int k = 0; k < NUM_COMMANDS && noOverlap; k++)
                     {
                       if (newCommand == commands[k])
                       {
                         noOverlap = false;
                       }
                     }
                     
                     if (noOverlap)
                     {
                       commands[i] = newCommand;
                     }
                     else
                     {
                       cout << newCommand << " command already exists" << endl;
                     }
                   }
                 }
                 
                 if (!found) // command not found
                 {
                   cout << origCommand << " command is not found" << endl;
                 }
                 break;      
      
      }
    }
    cout << board;
    board.draw();
  }
}
  

