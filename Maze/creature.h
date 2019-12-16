#pragma once



using namespace std;

class Creature
{

	int row, column;

public:

	
	Creature(int row, int column);
	int getRow();
	int getColumn();
	string Solve(Maze& maze);
	string solveHelper(Maze& maze, int currX, int currY);
	string getDirection(int d1, int d2);

};
