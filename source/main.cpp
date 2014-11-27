/***********************************************************************
  AUTHOR:	Joshua Carter.
  WARNING:	Hacky uncommented code inside.

  README:	-	You may look at any of the source code in this project 
				but it should be mostly unnecessary. 
			-	You only really need to	know that the Node class has an 
				x/y position and a vector of Node pointers (no edge 
				class is needed for this example).
			-	The FindPath function is called for you when a new graph
				is generated (by pressing the SPACE key).
			-	You will probably want to create another function to do
				the recursive walking of the graph and return the path
				it took from start to end.
			-	There are a few vector2 style operations in the Math.h
				file that you can use.
			-	Due to the framework used, link-lines cannot be drawn
				behind the nodes ._.
			
************************************************************************/

#include "AIE.h"
#include <cmath>
#include <vector>
#include "Node.h"
#include "NodeMap.h"
#include "Player.h"
#include "Math.h"
#include <iostream>

NodeMap* nodeMap;
Player* player;

//	THIS SECTION TO BE FILLED IN BY THE STUDENT ---------------------------------------------------------

std::vector<Node*>* FindPath()
{
	Node* start					= nodeMap->GetStart();
	Node* end					= nodeMap->GetEnd();

	std::vector<Node*>* path	= new std::vector<Node*>();

	// YOUR CODE GOES HERE
	using namespace std;
	cout << start->links.size() << endl;



	// YOUR CODE ENDS HERE

	return path;
}

//	-----------------------------------------------------------------------------------------------------
