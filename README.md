# Tetris

![Tetris](https://github.com/simon-qi/Tetris/blob/master/tetris.screenshot.PNG)

Tetris game written in C++ by Jonathan Zhao (https://github.com/qaovxtazypdl) and me

Calling make creates an executable named quadris.

The game only runs on Linux. 
The following commands are supported:

left - moves the current block one cell to the left. If this is not possible (left edge of the board,
or block in the way), the command has no effect.

right - as above, but to the right.

down - as above, but one cell downward.

clockwise - rotates the block 90 degrees clockwise, as described earlier. If the rotation cannot
be accomplished without coming into contact with existing blocks, the command has no effect.

counterclockwise - as above, but counterclockwise.

drop - drops the current block. It is (in one step) moved downward as far as possible until
it comes into contact with either the bottom of the board or a block. This command also
triggers the next block to appear. Even if a block is already as far down as it can go (as a
result of executing the down command), it still needs to be dropped in order to get the next
block.

levelup - Increases the difficulty level of the game by one. The block showing as next still
comes next, but subsequent blocks are generated using the new level. If there is no higher
level, this command has no effect.

leveldown - Decreases the difficulty level of the game by one. The block showing as next still
comes next, but subsequent blocks are generated using the new level. If there is no lower
level, this command has no effect.

restart - Clears the board and starts a new game.

rename oldname newname - Changes the name of the command from oldname to newname. It has no effect if oldname is not an existing command or newname already exists as a command.

hold - Holds the current block so that it can be used later. If a block is already held, the held block becomes the current block. After this command is issued, the drop command must be issued before this command has any effect again.

skip - Skips the current block if it is skippable.

End-of-file (EOF) terminates the game.

Only as much of a command as is necessary to distinguish it from other commands needs to be entered. For example, lef is enough to distinguish the left command from the levelup command, so the system should understand either lef or left as meaning left.

In addition, commands can take a multiplier prefix, indicating that that command should be executed some number of times. For example 3ri means move to the right by three cells. 

The following command line arguments are supported:

-text runs the program in text-only mode. No graphics are displayed. The default behaviour (no -text) is to show both text and graphics.

-seed xxx sets the random number generator's seed to xxx. If you don't set the seed, you always get the same random sequence every time you run the program. It's good for testing, but not much fun.

-scriptfile xxx Uses xxx instead of sequence.txt as a source of blocks for level 0.

-startlevel n Starts the game in level n. The game starts in level 0 if this option is not supplied.

-rename allows users to modify the names of commands using the rename command

-extralevels allows the game to be played with 6 levels instead of 4.

-hold allows blocks to be held using the hold command

-skip allows blocks to be skipped using the skip command.

We have modified the Xwindow class to make the blocks appear 3-D on the window. We accomplished this by drawing the border of the block using trapezoids that are of a different shade of colour than the rest of the block.

We received 107% on this project after the consideration of our bonus features.
