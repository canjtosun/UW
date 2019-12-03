#pragma once
#include <vector>
#include <string>
#include "creature.h"

using namespace std;


class Maze
{

	int widthOfMaze, heightOfMaze, rowExit, columnExit;
	string fileName;

public:

	vector<string> maze_board;
	vector<vector<bool>> visited;

	int getwidthOfMaze();
	int getheightOfMaze();
	int getrowExit();
	int getcolumExit();
	

	//Maze constructor requiring a valid file name
	explicit Maze(string mazeFile);
	Maze(int widthOfMaze, int heightOfMaze, int rowExit, int columnExit);

	friend ostream& operator<<(ostream& out, const Maze& maze);
	friend ostream &operator<<(ostream& out, const Creature& creature);

	bool IsClear(int row, int column)const;
	bool IsWall(int row, int column)const;
	bool IsPath(int row, int column)const;
	bool IsVisited(int row, int column)const;

	//mark the maze with *
	void MarkAsPath(int row, int column);

	//mark the maze with +
	void MarkAsVisited(int row, int column);


	//my funcs
	void assignFileToMatrix(string mazeFile);
	void printBoard();
	bool IsInBoard(int row, int column)const;


};
