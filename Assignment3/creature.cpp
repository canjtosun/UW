#include <iostream>
#include "maze.h"
#include "creature.h"
#include <fstream>
#include <string>

using namespace std;



//constructor, define starting point for 
//the creature
Creature::Creature(int row, int column)
{
	this -> row = row;
	this -> column = column;
}

//getters
int Creature::getRow() { return row; }
int Creature::getColumn() { return column; }

//return [N,E,S,W] depending on the
//change in x or y
string Creature::getDirection(int d1, int d2)
{
	if (d1 == 1) return "S"; //going south
	if (d1 == -1) return "N"; //going north
	if (d2 == 1) return "E"; // going east
	if (d1 == -1) return "W"; // going west

	return "";
}

/*
uses dfs to explore every adjacent cell
in search of a path to the exit point
*/
string Creature::solveHelper(Maze& maze, int currX, int currY)
{
	//base cases
	//if there is wall or the current cell has been
	//visited at some point in the current path
	//return X to indicate that no path exists
	//thru the current vertex.
	if (maze.IsWall(currX, currY) || maze.IsVisited(currX, currY))
		return "X";

	//if we found the path to the finish point
	if (currX == maze.getrowExit() && currY == maze.getcolumExit()) {
		maze.MarkAsPath(currX, currY);
		return "";
	}

	//visit the current cell
	maze.visited[currX][currY] = true;

	//mark the current cell + (visited)
	maze.MarkAsVisited(currX, currY);


	bool isDone = false;
	string result = "X";

	/*
	this nested for loops itereates every possible
	way that creature can go. there is 8 possible 
	way to go but we are skipping every diagonal
	moves and the place where creature.
	*/

	for (int d1 = -1; d1 <= 1; d1++)
	{
		//when we found the path to 
		//finish point, break the loop
		if (isDone) 
			break;
		for (int d2 = -1; d2 <= 1; d2++)
		{
			//ignores diagonal deltas
			//and current point
			if (abs(d1) == abs(d2))
				continue;

			/*
			determine the direction and 
			visit adjacent cells {N,S,E,W} of the
			current position 
			*/
			string temp = getDirection(d1, d2) + 
				solveHelper(maze, currX + d1, currY + d2);

			/*
			if the end of the string is not equal X
			that means we already found the path
			so break out of the loop and return the
			found path
			*/

			if (temp.back() != 'X') {
				result = temp;
				isDone = true;
				break;
			}
		}
	}

	//unvisit the current cell as we
	//are done exploring the current
	//path thru point (currX,currY)
	maze.visited[currX][currY] = false;

	//if the last char of string is not X
	//we found the exit so mark
	//the current cell as part of the path(*)
	if (result.back() != 'X')
		maze.MarkAsPath(currX, currY);
	return result;



}

//takes maze object,solves the maze
//and returns the solution
string Creature::Solve(Maze& maze)
{
	return solveHelper(maze, row, column);
}



