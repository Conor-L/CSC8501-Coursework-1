#pragma once
#include <vector>

struct Cell { int x; int y; bool visited = false; };

class Maze {	
	public:
		Maze();
		Maze(int dim_x, int dim_y, int num_exits); // Parameterised Constructor where the user can provide the information needed
		~Maze();

		void fill_maze();
		void generate_maze();
		void move_cell(Cell current_cell);
		void print_maze();

		void place_exit(int num_exits);
		void place_start(int startx, int starty);
		Cell create_exit_cell(int x, int y);
		int generate_random_number(int upper_limit, int lower_limit);

	private:
		char** maze;
		int maze_x_size = 0;
		int maze_y_size = 0;
		int num_exits = 1;

		Cell starting_cell;
		std::vector<Cell> exit_vector;

};