// ---------------------------graphl.cpp-------------------------------------
// Can Tosun CSS 343 C
// Feb 10 2020
// Feb 15, 2020 - Date of Last Modification
// ----------------------------------------------------------------------------
// Purpose - This file is an implementation for depth first search
// includes constructor, destructor, build graph from reading the file
// depth search first and helper for that function.
// ----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <algorithm> 
#include "nodedata.h"
#include "graphl.h"


using namespace std;

// -------------------------------Constructor------------------------------------ 
// Description: We are dealing with list so, assign all data and edgehead to
// nullptr and no visit.
// preconditions:	none
// postconditions:  all nodes vill be unvisited and null			   
// -------------------------------------------------------------------------------
GraphL::GraphL()
{
	size = 0;

	for (int i = 1; i < MAXNODES_DFS; i++)
	{
		way_array[i].data = nullptr;
		way_array[i].visited = false;
		way_array[i].edgeHead = nullptr;
	}
}

// -------------------------------Destructor------------------------------------ 
// Description: deleting all data and nodes and assigning to nullptr
// preconditions:	array must not be empty
// postconditions:  free out the memory leak.			   
// -------------------------------------------------------------------------------
GraphL::~GraphL()
{
	for (int i = 1; i <= size ; ++i)
	{
		EdgeNode* curr = way_array[i].edgeHead;
		delete way_array[i].data;

		while (curr != nullptr)
		{
			way_array[i].edgeHead = way_array[i].edgeHead->nextEdge;
			delete curr;
			curr = nullptr;
			curr = way_array[i].edgeHead;
		}
	}
}


// -------------------------------buildGraph------------------------------------ 
// Description: Reading the provided file and assign the values
// int the list.
// preconditions:	file must be in directory and well organized.
// postconditions:  values in file will build the graph correctly			   
// -------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& infile2)
{
	//get the size from first line
	infile2 >> size;
	string name;

	getline(infile2, name);

	//assign the datas to nodes
	for (int i = 1; i <= size; i++)
	{
		getline(infile2, name);
		NodeData* tmp = new NodeData(name);
		way_array[i].data = tmp;
	}

	//read first value to: from
	//read second value to: to
	int from, to;
	while (infile2 >> from >> to)
	{
		//when you hit 0, stop there
		if (from == 0)
			break;

		//if head is null, create new one and assign next to null
		if (way_array[from].edgeHead == nullptr)
		{
			EdgeNode* newNode = new EdgeNode;
			newNode->adjGraphNode = to;
			way_array[from].edgeHead = newNode;
			way_array[from].edgeHead->nextEdge = nullptr;
		}

		//else assign values there
		else
		{
			EdgeNode* newNode = new EdgeNode;
			newNode->adjGraphNode = to;
			newNode->nextEdge = way_array[from].edgeHead;
			way_array[from].edgeHead = newNode;
		}
	}
}

// -------------------------------displayGraph------------------------------------ 
// Description: printing out the graph as close as the file format.
// preconditions:	none
// postconditions:  print out(display) the graph			   
// -------------------------------------------------------------------------------
void GraphL::displayGraph()
{
	cout << "Graph: " << endl;

	for (int i = 1; i <= size; i++)
	{
		cout << "Node " << i << "\t" << *way_array[i].data << endl;
		cout << endl;

		EdgeNode* curr = way_array[i].edgeHead;

		while (curr != nullptr)
		{
			cout << i << " " << curr->adjGraphNode << endl;
			curr = curr->nextEdge;
		}
	}
}

// -------------------------------DFS ------------------------------------ 
// Description: checks the every node is not visited and find dfs order
// preconditions:	nodes should be not visited
// postconditions:  display the depth first order			   
// -------------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
	cout << "depth First Ordering : ";

	for (int i = 1; i <= size; i++)
	{
		if (!way_array[i].visited)
		{
			dfsHelper(i);
		}
	}
	cout << endl;

}

// -------------------------------dfsHelper------------------------------------ 
// Description: Helper for DFS function
// preconditions:	parameter v should be > 0
// postconditions:  displays the dfs order from V value			   
// -------------------------------------------------------------------------------
void GraphL::dfsHelper(int v)
{
	//print out v first
	cout << v << " ";

	//after u print out, make it visited
	way_array[v].visited = true;

	//curr is pointing to the head
	EdgeNode* curr = way_array[v].edgeHead;

	//as long as curr is not null
	//check if visisted, if not call it recursively
	while (curr != nullptr)
	{
		if (!way_array[curr->adjGraphNode].visited)
			dfsHelper(curr->adjGraphNode);

		curr = curr->nextEdge;
	}
}

