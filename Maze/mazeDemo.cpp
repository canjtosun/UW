#include <iostream>
#include "maze.h"
#include "creature.h"
#include <fstream>
#include <string>

using namespace std;

int main()
{
	
	Maze maze("maze1.txt");
	//cout << maze;
	//maze.printBoard();
	Creature creature(1,7);
	cout << creature.Solve(maze) << endl;
	maze.printBoard();
	

	return 0;
}
