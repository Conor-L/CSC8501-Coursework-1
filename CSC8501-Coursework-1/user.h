#pragma once
#include "maze.h"

class User : public Maze {
	public:
		User(std::string username);
		~User();

		Maze* generate_maze(int height, int width, int exits);
		void save_maze(Maze* maze, std::string filename);
		void load_maze(Maze* maze, std::string filename);

		std::string get_username() { return username; }

	private:
		std::string username;
};