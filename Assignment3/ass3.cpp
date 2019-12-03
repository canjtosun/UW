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
	Creature creature(2,14);
	cout << creature;
	cout << creature.Solve(maze) << endl;
	cout << maze;
	

	return 0;
}
