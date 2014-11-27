#include "NodeMap.h"

#include "Math.h"
#include "AIE.h"
#include <random>

struct LinkLine
{
	Node *from, *to;
	float x1, x2, y1, y2;
	SColour color;
};
std::vector<LinkLine> lines;

NodeMap::NodeMap(int screenWidth, int screenHeight)
{
	width = screenWidth, height = screenHeight;
	startTextureID = CreateSprite("./images/start.png", 32, 32, true);
	endTextureID = CreateSprite("./images/end.png", 32, 32, true);
	graph = std::vector<Node*>(50);
	lines = std::vector<LinkLine>(50);
	start = NULL, end = NULL;
}

NodeMap::~NodeMap()
{
	for(int i = 0; i < graph.size(); ++i)
		delete graph[i];
	graph.clear();
	lines.clear();
	start = NULL, end = NULL;
	DestroySprite(startTextureID);
	DestroySprite(endTextureID);
}

void NodeMap::GenerateGraph()
{
	//kill em
	for(int i = 0; i < graph.size(); ++i)
		delete graph[i];
	graph.clear();
	lines.clear();
	start = NULL, end = NULL;

	//spawn em
	for(int w = 0; w < width; w += 50)
	{
		for(int h = 0; h < height; h += 50)
		{
			graph.push_back(new Node(w + (rand() % 30), h + (rand() % 30)));
		}
	}

	//clean em
	auto iter = graph.begin();
	while(iter != graph.end())
	{
		Node* n = *iter;
		bool kill = false;

		if(n->x < 50 || n->x > width - 50 || n->y < 50 || n->y > height - 50)
			kill = true;

		for(int i = 0; i < graph.size(); ++i)
		{
			if(graph[i] == n)
				continue;
			else if(Distance(n->x, n->y, graph[i]->x, graph[i]->y) < 40)
			{
				kill = true;
				break;
			}
		}

		if(kill)
		{
			iter = graph.erase(iter);
			delete n;
			continue;
		}
		else
			iter++;
	}

	//link em
	for(int i = 0; i < graph.size(); ++i)
	{
		Node* n = graph[i];

		for(int j = 0; j < graph.size(); ++j)
		{
			if(i == j)
				continue;
			else if(Distance(n->x, n->y, graph[j]->x, graph[j]->y) < 80)
				n->links.push_back(graph[j]);
		}
	}

	//purge the unlinked
	iter = graph.begin();
	while(iter != graph.end())
	{
		Node* n = *iter;

		if(n->links.size() <= 0)
		{
			iter = graph.erase(iter);
			delete n;
			continue;
		}
		else if(n->links.size() == 1 &&	n->links[0]->links.size() == 1 && n->links[0]->links[0] == n)
		{
			iter = graph.erase(iter);
			n->links[0]->links.clear();
			delete n;
			continue;
		}

		iter++;
	}

	//store start and end points
	start = graph[rand() % graph.size()];
	end = start;
	while (end == start)
		end = graph[rand() % graph.size()];

	//make links
	for(int i = 0; i < graph.size(); ++i)
	{
		Node* from = graph[i];

		for(int j = 0; j < from->links.size(); ++j)
		{
			Node* to = from->links[j];

			LinkLine line;
			line.from = from, line.to = to;
			line.x1 = from->x, line.y1 = from->y;
			line.x2 = to->x, line.y2 = to->y;
			line.color = SColour(0, 255, 255, 255);
			lines.push_back(line);
		}
	}
}

void NodeMap::Draw()
{
	for(int i = 0; i < lines.size(); ++i)
	{
		LinkLine& l = lines[i];
		DrawLine((int)l.x1, (int)l.y1, (int)l.x2, (int)l.y2, l.color);
	}

	for(int i = 0; i < graph.size(); ++i)
		graph[i]->Draw();

	MoveSprite(startTextureID, start->x, start->y);
	DrawSprite(startTextureID);
	MoveSprite(endTextureID, end->x, end->y);
	DrawSprite(endTextureID);
}

Node* NodeMap::GetStart()
{
	return start;
}

Node* NodeMap::GetEnd()
{
	return end;
}

std::vector<Node*> NodeMap::GetGraph()
{
	return graph;
}

void NodeMap::ChangeLinkColor(Node* from, Node* to, char r, char g, char b)
{
	int count = 0;

	for(int i = 0; i < lines.size(); ++i)
	{
		LinkLine& l = lines[i];

		if((l.from == from && l.to == to) || (l.from == to && l.to == from))
		{
			l.color = SColour(r, g, b, 255);
			count++;
			if(count >= 2)
				break;
		}
	}
}