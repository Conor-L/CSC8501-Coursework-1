#include <iostream>
#include <time.h>
#include "maze.h"
#include <stack>

using namespace std;
Maze::Maze() {
	srand(time(NULL));

	maze = new Cell*[12];
	for (int i = 0; i < 12; i++) {
		maze[i] = new Cell[35];
	}

	maze_x_size = 11;
	maze_y_size = 34;

	fill_maze();
	place_start(maze_x_size / 2, maze_y_size / 2);
	set_neighbours();

	generate_maze(*starting_cell);
	generate_maze_centre();
	place_exit(num_exits);

}

Maze::Maze(int dim_x, int dim_y, int num_exits) {
	srand(time(NULL));

	maze_x_size = dim_x - 1;
	maze_y_size = dim_y - 1;
	this->num_exits = num_exits;

	maze = new Cell*[dim_x];
	for (int i = 0; i < dim_x; i++) {
		maze[i] = new Cell[dim_y];
	}

	fill_maze();	
	place_start(maze_x_size / 2, maze_y_size / 2);

	set_neighbours();
	generate_maze(*starting_cell);
	generate_maze_centre();
	place_exit(num_exits);

}
	
Maze::~Maze() {
	// Clean up
	for (int i = 0; i < maze_x_size + 1; i++) {
		delete[] maze[i];
	}
	delete[] maze;
}

void Maze::fill_maze() {
	for (int i = 0; i < (maze_x_size + 1); i++) {
		for (int j = 0; j < (maze_y_size + 1); j++) {
			maze[i][j].value = 'X';
			maze[i][j].x = i;
			maze[i][j].y = j;
			
		}
	}

	// Make sure the walls are actually registered as walls
	for (int i = 0; i < (maze_x_size + 1); i++) {
		for (int j = 0; j < (maze_y_size + 1); j++) {

			if ((j == 0) || (j == maze_y_size)) {
				maze[i][j].isWall = true;
			}

			else if ((i == 0) || (i == maze_x_size)) {
				maze[i][j].isWall = true;
			}

		}
	}
}

void Maze::set_neighbours() {
	// Set the neighours of each Cell
	// leftmost cells don't have a left neighbour
	// rightmost cells don't have a right neighbour

	for (int i = 0; i < (maze_x_size + 1); i++) {
		for (int j = 0; j < (maze_y_size + 1); j++) {
			if (j == 0 || j != maze_y_size) {
				maze[i][j].right_neighbour = &maze[i][j + 1];
			}

			if (j != 0) {
				maze[i][j].left_neighbour = &maze[i][j - 1];
			}

			if (i == 0 || i != maze_x_size) {
				maze[i][j].down_neighbour = &maze[i + 1][j];
			}

			if (i != 0) {
				maze[i][j].up_neighbour = &maze[i - 1][j];
			}
		}
	}
}

void Maze::generate_maze(Cell c) {
	Cell* initial_cell = &maze[c.x][c.y];
	stack<Cell*> path_stack;

	initial_cell->visited = true;
	path_stack.push(initial_cell);
	
	while (!path_stack.empty()) {
		Cell* current_cell = path_stack.top();
		path_stack.pop();
		vector<Cell*> available_neighbours;

		if (!check_space(*current_cell)) {
			available_neighbours = get_neighbours(*current_cell);
		}

		while (!available_neighbours.empty()) {
			int random = generate_random_number(available_neighbours.size(), 0); 
			Cell* next_cell = available_neighbours.at(random);
			// check space
			if (!check_space(*next_cell)) {
				path_stack.push(current_cell);
				next_cell->value = ' '; next_cell->visited = true;
				path_stack.push(next_cell);
			}
			available_neighbours.erase(available_neighbours.begin() + random);
		}
	}
	
}

vector<Cell*> Maze::get_neighbours(Cell current) {
	vector<Cell*> available_neighbours;
	
	if ((current.up_neighbour->visited == false) && (current.up_neighbour->isWall == false)) {
		available_neighbours.emplace_back(maze[current.x][current.y].up_neighbour);
	}
	
	if ((current.down_neighbour->visited == false) && (current.down_neighbour->isWall == false)) {
		available_neighbours.emplace_back(maze[current.x][current.y].down_neighbour);
	}

	if ((current.right_neighbour->visited == false) && (current.right_neighbour->isWall == false)) {
		available_neighbours.emplace_back(maze[current.x][current.y].right_neighbour);
	}
	
	if ((current.left_neighbour->visited == false) && (current.left_neighbour->isWall == false)) {
		available_neighbours.emplace_back(maze[current.x][current.y].left_neighbour);
	}
	
	return available_neighbours;

}

bool Maze::check_space(Cell check) {
	int space_count = 0;

	if (check.up_neighbour->visited == true) {
		space_count++;
	}

	if (check.down_neighbour->visited == true || check.down_neighbour->isWall == true) {
		space_count++;
	}

	if (check.left_neighbour->visited == true || check.left_neighbour->isWall == true) {
		space_count++;
	}

	if (check.right_neighbour->visited == true || check.right_neighbour->isWall == true) {
		space_count++;
	}

	if (check.up_neighbour->isWall == true || check.down_neighbour->isWall == true || check.left_neighbour->isWall == true || check.right_neighbour->isWall == true) {
		return (space_count > 2 ? true : false);
	}

	else {
		return (space_count > 1 ? true : false);
	}

}

void Maze::generate_maze_centre() {
	// Delete a 3 by 3 around the starting cell
	int startx = starting_cell->x;
	int starty = starting_cell->y;

	// Top 5 cells

	for (int i = starty - 2; i < starty + 3; i++) {
		maze[startx - 1][i].value = ' '; maze[startx - 1][i].visited = true;
	}

	// middle 5 cells
	for (int i = starty - 2; i < starty + 3; i++) {
		if (i == starty) {
			continue; // ignore starting cell
		}

		maze[startx][i].value = ' '; maze[startx - 1][i].visited = true;
	}

	// bottom 5 cells
	for (int i = starty - 2; i < starty + 3; i++) {
		maze[startx + 1][i].value = ' '; maze[startx - 1][i].visited = true;
	}

}

void Maze::print_maze() {
	for (int i = 0; i < (maze_x_size + 1); i++) {
		for (int j = 0; j < (maze_y_size + 1); j++) {
			cout << maze[i][j].value;
		}
		cout << endl;
	}
	cout << endl;
}

void Maze::place_exit(int num_exits) {
	// The exits should be placed somewhere that makes sense after the maze is generated.
	vector<Cell*> possible_exit_positions; // Before Neighbour Check
	vector<Cell*> confirmed_exit_positions; // After Neighbour Check
	
	for (int i = 0; i < maze_x_size + 1; i++) {
		for (int j = 0; j < maze_y_size + 1; j++) {
			// Ignore corners
			// Ignore walls that have a neighbour blocking an open path
			// so if top wall has bottom neighbour->can't place.

			if (!(i == 0 && j == 0) && !(i == 0 && j == maze_y_size) && !(i == maze_x_size && j == 0) && !(i == maze_x_size && j == maze_y_size)) {
				// Ignore corners
				possible_exit_positions.emplace_back(&maze[i][j]);
			}
		}
	}
	
	// Check neighbours
	
	for (int v = 0; v < possible_exit_positions.size(); v++) {
		Cell* current_cell = possible_exit_positions.at(v);

		if ((current_cell->x > 0 && current_cell->y == 0)) {
			if (current_cell->right_neighbour->value == ' ') {
				confirmed_exit_positions.emplace_back(current_cell);
			}
		}

		else if ((current_cell->x > 0 && current_cell->y == maze_y_size)) {
			if (current_cell->left_neighbour->value == ' ') {
				confirmed_exit_positions.emplace_back(current_cell);
			}
		}

		else if ((current_cell->x == 0 && current_cell->y > 0)) {
			if (current_cell->down_neighbour->value == ' ') {
				confirmed_exit_positions.emplace_back(current_cell);
			}
		}

		else if ((current_cell->x == maze_x_size && current_cell->y > 0)) {
			if (current_cell->up_neighbour->value == ' ') {
				confirmed_exit_positions.emplace_back(current_cell);
			}
		}

	}

	for (int k = 0; k < num_exits; k++) {
		int random_exit = generate_random_number(confirmed_exit_positions.size(), 0);
		confirmed_exit_positions.at(random_exit)->value = 'E';
	}
	
}

void Maze::place_start(int startx, int starty) {
	maze[startx][starty].value = 'S';
	starting_cell = &maze[startx][starty];
}

int Maze::generate_random_number(int upper_limit, int lower_limit) {
	return(rand() % upper_limit + lower_limit);
}

Cell Maze::create_exit_cell(int x, int y) {
	Cell exit_cell;
	exit_cell.x = x;
	exit_cell.y = y;

	return exit_cell;
}

void Maze::save_maze(Maze* maze, string filename) {
	ofstream ostream;

	ostream.open(filename + ".txt");
	if (!ostream) {
		cout << "There was an issue opening this file." << endl;
	}

	ostream << maze->maze_x_size + 1 << "|" << maze->maze_y_size + 1 << endl;
	ostream << maze->num_exits << endl;
	for (int i = 0; i < (maze->maze_x_size + 1); i++) {
		for (int j = 0; j < (maze->maze_y_size + 1); j++) {
			ostream << maze->maze[i][j].value;
		}
		ostream << endl;
	}

	if (!ostream) {
		cout << "There was an issue writing to this file." << endl;
	}

	ostream.close();

}

Maze* Maze::load_maze(string filename) {
	ifstream istream;

	istream.open(filename + ".txt");

	if (!istream) {
		cout << "There was an issue opening this file." << endl;
	}

	string dimensions;

	istream >> dimensions;

	int split = dimensions.find('|');
	int height = stoi(dimensions.substr(0, split));
	int width = stoi(dimensions.substr(split + 1));

	int exits;
	istream >> exits;

	Maze* new_maze = new Maze(height, width, exits);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			char c;

			c = istream.get();

			if (c == '\n') {
				c = istream.get();
			}

			new_maze->maze[i][j].value = c;
			
		}
	}

	new_maze->print_maze();

	if (!istream) {
		cout << "There was an issue reading this file." << endl;
	}

	istream.close();

	return new_maze;

}