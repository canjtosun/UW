// -------------------------------myTestFile.cpp--------------------------------
// Can Tosun CSS 343 C
// Feb 10 2020
// Feb 15, 2020 - Date of Last Modification
// ----------------------------------------------------------------------------
// Purpose - This file contains instrutor's lab3.cpp file 
// and my extra test cases
// ----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "graphl.h"
#include "graphm.h"
using namespace std;

int main() {


	// part 1 instructor's test
	ifstream infile1("data31.txt");
	if (!infile1) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the shortest path from every node to all other nodes
	for (;;) {
		GraphM G;
		G.buildGraph(infile1);
		if (infile1.eof())
			break;
		G.findShortestPath();
		G.displayAll();              // display shortest distance, path to cout
		G.display(3, 1);              // display path from node 3 to 1 to cout
		G.display(1, 2);
		G.display(1, 4);

	}

	cout << "------------------" << endl;
	cout << "------------------" << endl;

	//testfile, my test file txt provided
	ifstream infile11("testData.txt");
	if (!infile11) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	GraphM G2;
	G2.buildGraph(infile11); //buildgraph
	G2.findShortestPath(); //find shortest path
	G2.displayAll(); //display all  
	G2.display(2, 3);  //display particular route           
	G2.display(3, 2); //display particular route      
	G2.display(1, 5); //display particular route   
	cout << "------------------" << endl;
	cout << "------------------" << endl;


	ifstream infile22("dataUWB.txt");
	if (!infile22) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	GraphM G3;
	G3.buildGraph(infile22); //buildgraph
	G3.findShortestPath(); //find shortest path
	G3.displayAll(); //display all  
	G3.display(2, 3);  //display particular route           
	G3.display(3, 2); //display particular route      
	G3.display(1, 5); //display particular route 
	G3.display(0, 0); //error
	G3.display(-1, 4); //error

	cout << "------------------" << endl;
	cout << "------------------" << endl;



	// part 2 
	ifstream infile2("data32.txt");
	if (!infile2) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the depth-first search ordering
	for (;;) {
		GraphL G;
		G.buildGraph(infile2);
		if (infile2.eof())
			break;
		G.displayGraph();
		G.depthFirstSearch();    // find and display depth-first ordering to cout
	}

	cout << "------------------" << endl;
	cout << "------------------" << endl;

	//mytest for DFS
	ifstream infile33("testData2.txt");
	if (!infile33) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	GraphL G4;
	G4.buildGraph(infile33); //build file
	G4.displayGraph(); //display graph
	G4.depthFirstSearch(); //show dfs order


	cout << endl;
	return 0;
}
