#pragma once
#include <vector>

struct Cell { 
	char value = ' '; 
	int x = 0; 
	int y = 0; 
	bool visited = false; 
	bool isWall = false;
	Cell* up_neighbour = nullptr;
	Cell* down_neighbour = nullptr;
	Cell* left_neighbour = nullptr;
	Cell* right_neighbour = nullptr;
};

class Maze {	
	public:
		Maze();
		Maze(int dim_x, int dim_y, int num_exits); // Parameterised Constructor where the user can provide the information needed
		~Maze();

		void fill_maze();
		void set_neighbours();
		void generate_maze(Cell initial);
		std::vector<Cell*> get_neighbours(Cell current_cell);
		bool check_space(Cell cell_to_check);
		void print_maze();

		void place_exit(int num_exits);
		void place_start(int startx, int starty);
		Cell create_exit_cell(int x, int y);
		int generate_random_number(int upper_limit, int lower_limit);

	private:
		Cell** maze;
		int maze_x_size = 0;
		int maze_y_size = 0;
		int num_exits = 1;

		Cell* starting_cell;
		std::vector<Cell> exit_vector;

};