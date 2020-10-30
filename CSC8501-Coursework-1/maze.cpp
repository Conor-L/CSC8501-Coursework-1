#include <iostream>
#include <time.h>
#include "maze.h"

using namespace std;
Maze::Maze() {
	srand(time(NULL));

	maze = new char*[12];
	for (int i = 0; i < 12; i++) {
		maze[i] = new char[35];
	}

	maze_x_size = 11;
	maze_y_size = 34;
	fill_maze();

	place_exit(num_exits);
	place_start(maze_x_size / 2, maze_y_size / 2);
	

}

Maze::Maze(int dim_x, int dim_y, int num_exits) {
	srand(time(NULL));

	maze_x_size = dim_x - 1;
	maze_y_size = dim_y - 1;
	this->num_exits = num_exits;

	maze = new char* [dim_x];
	for (int i = 0; i < dim_x; i++) {
		maze[i] = new char[dim_y];
	}

	fill_maze();

	place_exit(num_exits);
	place_start(maze_x_size / 2, maze_y_size / 2);

}
	
Maze::~Maze() {
	// Clean up
	for (int i = 0; i < maze_x_size + 1; i++) {
		delete[] maze[i];
	}

}

void Maze::fill_maze() {
	for (int i = 0; i < (maze_x_size + 1); i++) {
		for (int j = 0; j < (maze_y_size + 1); j++) {
			maze[i][j] = 'X';
		}
	}
}

void Maze::generate_maze() {
	// Place the exit and start cells dentored by E and S respectively
	// Start: (x/2, y/2)
	// Exit: (0, y) or (x, 0)
	// Use the depth first algorithm to generate the maze
	// Start from the centre cell and continually branch out until maze is completed.
	// Maze walls will be denoted by X
}

void Maze::print_maze() {
	for (int i = 0; i < (maze_x_size + 1); i++) {
		for (int j = 0; j < (maze_y_size + 1); j++) {
			cout << maze[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void Maze::place_exit(int num_exits) {
	for (int i = 0; i < num_exits; i++) {
		int side = generate_random_number(4, 0);
		int x_C;
		int y_C;

		switch (side) {
		case 0:
			x_C = generate_random_number(maze_x_size, 0);
			y_C = 0;
			break;
		case 1:
			x_C = 0;
			y_C = generate_random_number(maze_y_size, 0);
			break;
		case 2:
			x_C = generate_random_number(maze_x_size, 0);
			y_C = maze_y_size;
			break;
		case 3:
			x_C = maze_x_size;
			y_C = generate_random_number(maze_x_size, 0);
			break;
		default:
			x_C = generate_random_number(maze_x_size, 0);
			y_C = 0;
		}

		// Make sure the exits are not in the corners otherwise there is no valid path
		if ((x_C == 0 && y_C == 0) || (x_C == 0 && y_C == maze_y_size)) {
			maze[x_C + 1][y_C] == 'E' ? i -= 1 : maze[x_C + 1][y_C] = 'E';
		}		

		else if ((x_C == maze_x_size && y_C == 0) || (x_C == maze_x_size && y_C == maze_y_size)) {
			maze[x_C - 1][y_C] == 'E' ? i -= 1 : maze[x_C + 1][y_C] = 'E';
		}

		else {
			maze[x_C][y_C] == 'E' ? i -= 1 : maze[x_C][y_C] = 'E';
		}

	}
}

void Maze::place_start(int startx, int starty) {
	maze[startx][starty] = 'S';
}

int Maze::generate_random_number(int upper_limit, int lower_limit) {
	return(rand() % upper_limit + lower_limit);
}

int main() {
	//Maze* test_maze = new Maze();
	//test_maze->print_maze();

	Maze* test_parameter_maze = new Maze(15, 15, 3);
	test_parameter_maze->print_maze();
	return 0;
}