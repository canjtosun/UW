// -----------------------------------------------graphm.h-----------------------------------------
// Can Tosun CSS 343 C
// Feb 10 2020
// Feb 15, 2020 - Date of Last Modification
// -----------------------------------------------------------------------------------------------------
// Purpose - This file provided by instructor. 
// findPath function is finding the path
// findData is finding the data from source to dest path
// -----------------------------------------------------------------------------------------------------
#include <iostream>
#include "nodedata.h"



using namespace std;

const int MAXNODES = 101;

class GraphM {

public:

	GraphM();
	void buildGraph(ifstream&);
	bool insertEdge(int from, int to, int dist);
	bool removeEdge(int from, int to);
	void findShortestPath();
	void displayAll();
	void display(int from, int to);



private:

	struct TableType {

		bool visited;          // whether node has been visited
		int dist;              // shortest distance from source known so far
		int path;              // previous node in path of min dist

	};

	NodeData data[MAXNODES];              // data for graph nodes
	int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
	int size;                             // number of nodes in the graph
	GraphM::TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path
	void findPath(int from, int to);
	void findData(int from, int to);

};
