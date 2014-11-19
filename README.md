####Flood Tile Game
This game is based on the popular Flood It game, and provides output both on the commandline and in an X11 Window.

**Goal**: Change the color of the (0,0) cell until all cells are the same color. All cells touching (0,0) with the same colour would also change the color of their neighbouring cells as well.

**How to Play:**

new n: Creates a new n x n grid. 
random: Randomly initializes the board.
init: Allows manual initialization. Enter r c s, which represents the row, column and state to change that cell to. Enter -1 -1 to exit init mode.
include filex: Initializes using the r c s contained in filex. filex need not end with -1 -1.
game g: Starts a new game with g moves remaining.
switch s: Switch the (0,0) to state s.
?: Prints out the encoding between command line and the graphics.


**Graphics Encoding:**
```
0 White
1 Black
2 Red
3 Green
4 Blue
```
