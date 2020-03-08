// -------------------------------graphm.cpp--------------------------------
// Can Tosun CSS 343 C
// Feb 10 2020
// Feb 15, 2020 - Date of Last Modification
// ----------------------------------------------------------------------------
// Purpose - This file is an implementation for Dijkstra's algorithm
// includes constructor, build graph from reading the file
// insert and remove edge, display all shortest path from all sources to
// all destinations and display particular path.
// ----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <algorithm> 
#include "nodedata.h"
#include "graphm.h"
#include <set>
#include <limits.h>

using namespace std;

// -------------------------------Constructor------------------------------------ 
// Description: We are dealing with 2D array as matrix so assign all matrix to
// infinit value and no visit. also size and path is 0
// preconditions:	none
// postconditions:  matrix will be all int max and not visited		   
// -------------------------------------------------------------------------------
GraphM::GraphM()
{
	size = 0;

	for (int i = 1; i < MAXNODES; i++)
	{
		for (int j = 1; j < MAXNODES; j++)
		{
			C[i][j] = INT_MAX;
			T[i][j].dist = INT_MAX;
			T[i][j].visited = false;
			T[i][j].path = 0;
		}
	}
}

// -------------------------------buildGraph------------------------------------ 
// Description: Reading the provided file and assign the values
// int the list.
// preconditions:	file must be in directory and well organized.
// postconditions:  values in file will build the graph correctly			   
// -----------------------------------------------------------------------------

void GraphM::buildGraph(ifstream& infile1)
{
	//first line is size
	infile1 >> size;
	string name;

	getline(infile1, name);

	//get the values and set the data(street names)
	for (int i = 1; i <= size; i++)
		data[i].setData(infile1);

	// reading 3 values, source, destination and distance
	int from, to, distance;
	while (infile1 >> from >> to >> distance)
	{
		//stop when you hit 0
		if (from == 0)
			break;

		insertEdge(from, to, distance);
	}
}

// -------------------------------insertEdge------------------------------------ 
// Description: Inserting an edge to the graph
// preconditions:	paramters cannot be less than zero, more than size
// and equals, distance cannot be less then 1
// postconditions:  inserting an edge to the graphand return true, 
// otherwise return false
// -----------------------------------------------------------------------------
bool GraphM::insertEdge(int from, int to, int dist)
{
	//validation
	if (from < 1 || from > size)
		return false;
	//validation
	if (to < 1 || to > size)
		return false;
	//validation
	if (dist < 1 || from == to)
		return false;

	//assign source dest and distance
	C[from][to] = dist;

	return true;
}

// -------------------------------removeEdge------------------------------------ 
// Description: Removing an edge from the graph
// preconditions: paramters cannot be less than 1, more than size
// postconditions:  removeing an edge from the graph and return true, 
// otherwise return false
// -----------------------------------------------------------------------------
bool GraphM::removeEdge(int from, int to)
{
	//validation
	if (from < 1 || from > size)
		return false;
	//validation
	if (to < 1 || to > size)
		return false;

	//assign it to int max as we did in consturtor
	//and update the shortest path
	C[from][to] = INT_MAX;
	findShortestPath();
	return true;
}

// ------------------------Disjkstra Shortest Path------------------------------ 
// Description: Finding to path from every node to every other node
// find the shortest path between every node to every other node in the graph,
// i.e., TableType T is updated with shortest path information
// preconditions: graph must be build
// postconditions:  find shortest path 
// -----------------------------------------------------------------------------
void GraphM::findShortestPath()
{
	
	//from source to size
	for (int source = 1; source <= size; source++)
	{
		//if soruce to destination is same, assign to 0
		T[source][source].dist = 0;

/*
We will use the set to store that information, and also
find the vertex with the shortest distance with it.
It kinda acts like a queue. The main loops executes 
until there are no more vertices in the set/queue. 
A vertex with the smallest distance gets extracted, 
and for each successful relaxation we first remove the old pair, 
and then after the relaxation add the new pair into the queue.
*/
		set<pair<int, int>> dijkQueue;
		dijkQueue.insert({ 0,source });

		//as long as size is more than 0
		while (dijkQueue.size() > 0)
		{
			//assign v to next node
			int v = dijkQueue.begin()->second;
			//delete the first
			dijkQueue.erase(dijkQueue.begin());

			//loop thru the size
			for (int i = 1; i <= size; i++)
			{
				//if it is not max int
				if (C[v][i] != INT_MAX)
				{
					if (T[source][v].dist + C[v][i] < T[source][i].dist)
					{
						//remove old one from queue and assign smaller value
						dijkQueue.erase({ T[source][i].dist,i });
						T[source][i].dist = T[source][v].dist + C[v][i];

						//insert the smaller value to the queue
						dijkQueue.insert({ T[source][i].dist,i });
						T[source][i].path = v;
					}
				}
			}
		}

	}
}

// -------------------------------displayAll------------------------------------ 
// Description: Displaying the Dijkstra as close as the instructor output
// preconditions: none
// postconditions: prints out the table
// -----------------------------------------------------------------------------
void GraphM::displayAll()
{
	cout << "Description" << setw(20) << "From node" << setw(10) << "To node"
		<< setw(14) << "Dijkstra's" << setw(7) << "Path" << endl;

	for (int from = 1; from <= size; from++)
	{
		cout << data[from] << endl;

		for (int to = 1; to <= size; to++)
		{

			if (T[from][to].dist != 0)
			{
				cout << setw(27) << from;
				cout << setw(10) << to;

				if (T[from][to].dist == INT_MAX)
					cout << setw(12) << "---" << endl;

				else
				{
					cout << setw(12) << T[from][to].dist;
					cout << setw(10);

					findPath(from, to);
					cout << endl;
				}
			}
		}
	}
}

// -------------------------------display------------------------------------ 
// Description: display particular source to destination distance and the path
// preconditions: do not print if distance int max, parameters cannot be zero
// postconditions:  display the particular path and data
// -----------------------------------------------------------------------------
void GraphM::display(int from, int to)
{
	if (from < 1 || to < 1)
	{
		cout << "Source or destination is less than 1" << endl;
		return;
	}
		

	if (T[from][to].dist == INT_MAX)
	{
		cout << from << " " << to << " " << "---" << endl;
		return;
	}

	cout << from << " " << to << " " << T[from][to].dist << " ";
	findPath(from, to);
	cout << endl;
	findData(from, to);

}

// -------------------------------findPath------------------------------------ 
// Description: Removing an edge from the graph
// preconditions: paramters cannot be less than 1, more than size
// postconditions:  removeing an edge from the graph and return true, 
// otherwise return false
// -----------------------------------------------------------------------------
void GraphM::findPath(int from, int to)
{
	//if source and dest is same, just print dest.
	if (from == to)
	{
		cout << to << " ";
		return;
	}

	int result = to;
	to = T[from][to].path;

	//call recursively
	findPath(from, to);

	//print
	cout << result << " ";
}
// -------------------------------findData------------------------------------ 
// Description: Removing an edge from the graph
// preconditions: paramters cannot be less than 1, more than size
// postconditions:  removeing an edge from the graph and return true, 
// otherwise return false
// -----------------------------------------------------------------------------
void GraphM::findData(int from, int to)
{
	//if distance infinite, return nothing.
	if (T[from][to].dist == INT_MAX)
		return;


	if (from == to)
	{
		cout << data[to] << endl;
		return;
	}

	int node = to;

	//call recursively
	findData(from, T[from][to].path);

	//print
	cout << endl;
	cout << data[node] << endl;

}




