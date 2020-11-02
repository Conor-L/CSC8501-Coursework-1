#include <iostream>
#include "user.h"
#include "maze.h"

using namespace std;

User::User(string username) {
	this->username = username;
}

Maze* User::generate_maze(int h, int w, int e) {
	// Make a call to the Maze class
	Maze* maze_gen = new Maze(h, w, e);
	maze_gen->print_maze();

	return maze_gen;
}

void User::save_maze(Maze* m, string f) {
	m->save_maze(m, f);
}

void User::load_maze(Maze* m, string filename) {
	m->load_maze(filename);
}

int main() {
	cout << "Files will be saved under User1 followed by the file name you provide." << endl;
	User* maze_user = new User("User1");

	bool keep_running = true;

	while (keep_running) {
		cout << "Choose an option using one of the numbers below: " << endl;
		cout << "(1) Generate a Maze" << endl;
		cout << "(2) Load a previous Maze" << endl;
		cout << "(3) Exit the program" << endl;

		int choice;
		cout << "-> ";
		cin >> choice;

		int width = 35;
		int height = 12;
		int exits = 1;
		string filename;

		Maze* generated_maze = new Maze();

		switch (choice) {
			case 1:
				// Generate a Maze
				cout << "How wide do you want the maze to be ? (inputs below 35 will be defaulted): ";
				cin >> width;

				width < 35 ? width = 35 : width;

				cout << "How high do you want the maze to be ? (inputs below 12 will be defaulted): ";
				cin >> height;

				height < 12 ? height = 12 : height;

				cout << "How many exits do you want ? (1 or more): ";
				cin >> exits;

				exits < 1 ? exits = 1 : exits;

				generated_maze = maze_user->generate_maze(height, width, exits);

				cout << "Do you want to save this maze? " << endl;

				int save;
				cout << "(1) Yes " << endl;
				cout << "(2) No " << endl;
				cout << "-> ";
				cin >> save;

				switch (save) {
					case 1:
						cout << "Please enter a suitable filename - do not include special characters or spaces: ";
						cin >> filename;
						filename = maze_user->get_username() + "-" + filename;

						maze_user->save_maze(generated_maze, filename);
						break;
					case 2:
						cout << "Saving will not occur." << endl;
						break;
					default:
						cout << "That was not an option - saving will not occur" << endl;
						break;
				}

				break;
			case 2:
				// Load a Previous Maze
				cout << "Please enter the file name that you wish to load: ";
				cin >> filename;
				maze_user->load_maze(generated_maze, filename);
				break;
			case 3:
				// Exit the program
				cout << "Goodbye!" << endl;
				keep_running = false;
				break;
			default :
				// Try again
				cout << "That was not one of the options - try again." << endl;
				break;
		}
	}

}