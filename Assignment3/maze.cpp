#include <iostream>
#include "maze.h"
#include "creature.h"
#include <fstream>
#include <string>
#include <vector>


using namespace std;

//getters
int Maze::getwidthOfMaze() { return widthOfMaze; }
int Maze::getheightOfMaze() { return heightOfMaze; }
int Maze::getrowExit() { return rowExit; }
int Maze::getcolumExit() { return columnExit; }

//assignnig maze file and
//assigning file to matrix
Maze::Maze(string mazeFile)
{
	fileName = mazeFile;
	assignFileToMatrix(mazeFile);
}

//initiate the private vars
Maze::Maze(int widthOfMaze, int heightOfMaze, int rowExit, int columnExit)
{
	this->widthOfMaze = widthOfMaze;
	this->heightOfMaze = heightOfMaze;
	this->rowExit = rowExit;
	this->columnExit = columnExit;
}


//print board function
void Maze::printBoard()
{
	for (int i = 0; i < maze_board.size(); i++)
		cout << maze_board[i] << endl;
}


//reading file and assigning
//to the matrix. return warning and exit 
//the program if no file there
void Maze::assignFileToMatrix(string mazeFile)
{
	ifstream readFile;
	readFile.open(mazeFile);

	if (!readFile.is_open()) {
		cout << "file is not here" << endl;
		exit(1);
	}

	string line = "";

	//read first 4 number and assign first
	readFile >> widthOfMaze >> heightOfMaze >> rowExit >> columnExit;
	
	//get rid of blank line
	getline(readFile, line);

	//assign
	while (getline(readFile, line))
	{
		maze_board.push_back(line);
	}

	//assign other vector's size
	visited.resize(maze_board.size(), vector<bool> (maze_board[0].size(), false));

}



//if is in board and if no wall
//means clear
bool Maze::IsClear(int row, int column) const
{
	return (IsInBoard(row, column) && !IsWall(row,column));
}

//if is in board and if match with x
//means there is wall there
bool Maze::IsWall(int row, int column) const
{
	return (IsInBoard(row,column) &&  maze_board[row][column] == 'x');
}

//if blank space
//mean there is path
bool Maze::IsPath(int row, int column) const
{
	return (maze_board[row][column] == ' ');
}

//if the visited vector is true
//means visited
bool Maze::IsVisited(int row, int column) const
{
	return (visited[row][column]);
}

//mark with * all path to exit
void Maze::MarkAsPath(int row, int column)
{
	maze_board[row][column] = '*';
}

//mark with + all visited spots
void Maze::MarkAsVisited(int row, int column)
{
	maze_board[row][column] = '+';
}

//helper method
//it checks the boundry
bool Maze::IsInBoard(int row, int column) const
{
	if (row < 0 || row >= maze_board.size() ||
		column < 0 || column >= maze_board[0].size())
		return false;
	return true;
}


//ostream overload
ostream& operator<<(ostream& out, const Maze& maze)
{
	out << maze.widthOfMaze << " by " << maze.heightOfMaze << " and row exit is : " <<
		maze.rowExit << " and col exit is: " << maze.columnExit;
	return out;
}

ostream& operator<<(ostream& out, const Creature& creature)
{
	out << "creature current point is : " << creature.
}










