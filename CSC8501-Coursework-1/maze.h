#pragma once

class Maze {
	public:
		Maze();
		Maze(int dim_x, int dim_y, int num_exits); // Parameterised Constructor where the user can provide the information needed
		~Maze();

		void fill_maze();
		void generate_maze();
		void print_maze();

		void place_exit(int num_exits);
		void place_start(int startx, int starty);
		int generate_random_number(int upper_limit, int lower_limit);

	private:
		char** maze;
		int maze_x_size = 0;
		int maze_y_size = 0;
		int num_exits = 1;

};