#include "Player.h"
#include "NodeMap.h"
#include "AIE.h"

std::vector<Node*>* FindPath();
extern NodeMap* nodeMap;

Player::Player(float _x, float _y)
{
	x = _x, y = _y, rotation = 0;
	textureID = CreateSprite("./images/player.png", 32, 32, true);
	path = std::vector<Node*>();
	next = NULL;
}

Player::~Player()
{
	DestroySprite(textureID);
	path.clear();
}

void Player::GeneratePath()
{
	path.clear();
	next = NULL;
	x = nodeMap->GetStart()->x;
	y = nodeMap->GetStart()->y;
	path = *FindPath();
}

void Player::Update(float dt)
{
	if(path.empty())
		return;

	if(next == NULL)
		next = path.back();

	float xDir = next->x - x, yDir = next->y - y;
	Normalise(xDir, yDir);

	rotation = DirToRot(xDir, yDir);

	x += xDir * dt * 400;
	y += yDir * dt * 400;

	if(Distance(x, y, next->x, next->y) < 3)
	{
		path.pop_back();
		if(path.size() > 0)
			nodeMap->ChangeLinkColor(next, path.back(), 255, 0, 0);
		next = NULL;
	}
}

void Player::Draw()
{
	RotateSprite(textureID, rotation);
	MoveSprite(textureID, x, y);
	DrawSprite(textureID);
}