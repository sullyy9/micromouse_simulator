Year 2 university prject
This is a micro-mouse simulator designed for testing exploration and solving algorithms. The maze is displayed in the console using ASCII characters. It currently runs a floodfill based algorithm.

The mouse is represented as a blue arrow: A, >, V or <
Walls are coloured white if the mouse doesn't know about them, green if it does.
The red numbers in each cell are that cells distance from the current mouses target.



To load a different maze go to the Maze.c file. Edit the line: fp = fopen("apec1988.maz", "r");  Change 'apec1988.maz' to whatever maze you want to load. Available mazes can be seen in the main folder. Make sure the maze you want to open is 16x16.
There is a number of options at the end of the main loop. Hopefully their self explanatory.
