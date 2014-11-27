#pragma once

#include <vector>
#include "Node.h"
#include "Math.h"

class Player
{
public:
	Player(float _x, float _y);
	~Player();

	void GeneratePath();
	void Update(float dt);
	void Draw();

private:	
	float x, y, rotation;
	int textureID;
	std::vector<Node*> path;
	Node* next;
};