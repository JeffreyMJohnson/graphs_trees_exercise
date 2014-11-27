#include "Node.h"
#include "AIE.h"

Node::Node(float _x, float _y)
{
	x = _x, y = _y;
	textureID = CreateSprite("./images/node.png", 16, 16, true);
}

Node::~Node()
{
	DestroySprite(textureID);
}

void Node::Draw()
{
	MoveSprite(textureID, x, y);
	DrawSprite(textureID);
}