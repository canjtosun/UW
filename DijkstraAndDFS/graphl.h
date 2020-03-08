// -----------------------------------------------graphl.h-----------------------------------------
// Can Tosun CSS 343 C
// Feb 10 2020
// Feb 15, 2020 - Date of Last Modification
// -----------------------------------------------------------------------------------------------------
// Purpose - This file provided by instructor. 
// dfsHelper is a function to help call depthfirstsearch function
// -----------------------------------------------------------------------------------------------------
#include <iostream>
#include "nodedata.h"


using namespace std;

//we do not use 0 value. the loops starts from 1
//so we need 101 constants, not 100.
const int MAXNODES_DFS = 101;

class GraphL {

public:

	GraphL();
	~GraphL();

	void buildGraph(ifstream& infile2);
	void depthFirstSearch();
	void displayGraph();


private:

	int size;

	struct EdgeNode;  // forward reference for the compiler

	struct GraphNode {    // structs used for simplicity, use classes if desired

		EdgeNode* edgeHead; // head of the list of edges
		NodeData* data;     // data information about each node
		bool visited;
	};

	GraphNode way_array[MAXNODES_DFS];

	struct EdgeNode {

		int adjGraphNode;  // subscript of the adjacent graph node
		EdgeNode* nextEdge;
	};

	void dfsHelper(int v);
};
