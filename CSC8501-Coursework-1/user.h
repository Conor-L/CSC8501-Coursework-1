#pragma once
#include <iostream>
#include "maze.h"

class User : public Maze {
	public:
		User(std::string username);

		Maze* generate_maze(int height, int width, int exits);
		Maze* generate_shortest_route(Maze* m);
		Maze* generate_all_routes(Maze* m);
		void save_maze(Maze* maze, std::string filename);
		void load_maze(Maze* maze, std::string filename);

		std::string check_string(std::string s);
		int check_integer_input(int input);

		std::string get_username() { return username; }
		void set_username(std::string s) { this->username = s; }

		int get_warning_limit() { return WRN_LIMIT; }

		int get_height_lower() { return height_lower; }
		int get_width_lower() { return width_lower; }
		int get_exit_lower() { return exit_lower; }

		int get_height_upper() { return height_upper; }
		int get_width_upper() { return width_upper; }
		int get_exit_upper() { return exit_upper; }

	private:
		std::string username;
		std::string const ALLOWED_CHARACTERS = "abcdefghijklmnopqrstuvwxyz-ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
		int const WRN_LIMIT = 5000;

		int height_lower = 12;
		int width_lower = 35;
		int exit_lower = 1;

		int height_upper = 100;
		int width_upper = 200;
		int exit_upper = (height_upper * width_upper) - 4;
};