#pragma once

#include "Node.h"
#include <vector>

class NodeMap
{
public:
	NodeMap(int screenWidth, int screenHeight);
	~NodeMap();

	void GenerateGraph();
	void Draw();

	Node* GetStart();
	Node* GetEnd();
	std::vector<Node*> GetGraph();
	void ChangeLinkColor(Node* from, Node* to, char r, char g, char b);

private:
	int startTextureID;
	int endTextureID;
	int width, height;
	std::vector<Node*> graph;
	Node *start, *end;
};

