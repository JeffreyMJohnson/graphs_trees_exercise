#pragma once

#include <vector>

class Node
{
public:
	Node(float _x, float _y);
	~Node();

	void Draw();
	
	float x, y;
	std::vector<Node*> links;

private:
	int textureID;
};