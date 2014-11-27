#include "AIE.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>
#include <iostream>
#include <vector>

#include "Node.h"
#include "NodeMap.h"
#include "Player.h"

extern NodeMap* nodeMap;
extern Player* player;

int main( int argc, char* argv[] )
{	
    Initialise(1024, 768, false, "Test Game");

	nodeMap = new NodeMap(1024, 768);
	nodeMap->GenerateGraph();
	player = new Player(nodeMap->GetStart()->x, nodeMap->GetStart()->y);	
	player->GeneratePath();

    do 
    {
        ClearScreen();
        float dt = GetDeltaTime();
		static bool down = false;

		if(IsKeyDown(' '))
		{
			if(!down)
			{
				nodeMap->GenerateGraph();
				player->GeneratePath();
				down = true;
			}
		}
		else
			down = false;

		player->Update(dt);
		nodeMap->Draw();
		player->Draw();

    } while ( FrameworkUpdate() == false );

	delete player;
	delete nodeMap;
    Shutdown();

    return 0;
}