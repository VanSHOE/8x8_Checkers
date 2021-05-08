# 8x8 Checkers project by Team 34
### Alphabetically - Hardik, Mayank, Nachiket, Rahul, Sukhjinder






The game can be compiled simply by cloning the git repo and running gcc checkers.c with additional parameters if desired.
The controls are mentioned in the instructions.txt, which can also be accessed in-game by pressing H

To control the cursor in the menu, use 'w' and 's'
and to change the difficulty in the menu, hover over difficulty and use 'a' and 'd'; note, this only affects the single-player mode

Now the user may select multiplayer or single-player as desired, and the game will be initialised. 
The game can be controlled using WASD to control the red square and space for selection/deselection.
Once a successful selection is made, selecting another square will move the desired piece if the move is illegal; else, no move will happen.

The multi jump rule in our game dictates that once a player makes a capture, if any other piece of that player can make a capture, the player is granted another turn.

At any point in time, the user can see the instructions to use several of the available features such as review, undo, etc.

Note- The undo function, while reverses a single move in 2 player mode, will go back to the last player-made move when it comes to single-player.  
That is it on how to run and play this game, have fun :)





#### External Libraries used
rlutil: https://github.com/tapio/rlutil
