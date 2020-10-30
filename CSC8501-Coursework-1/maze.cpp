#include <iostream>
#include "maze.h"

using namespace std;
Maze::Maze() {
	// Default Constructor
	// Generate a maze that is 35x12 squares
	// One exit
	// Start in the centre (Calculate the centre node (so its located at 35/2, 12/2))
}

Maze::~Maze() {
	// Clean up
}

void Maze::depth_first() {
	// Place the exit and start cells
	// Start: (x/2, y/2)
	// Exit: (0, y) or (x, 0)
	// Use the depth first algorithm to generate the maze
	// Start from the centre cell and continually branch out until maze is completed.
	// Maze walls will be denoted by X
}

int main() {
	return 0;
}