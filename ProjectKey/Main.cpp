#include <iostream>

#include "Game.h"
#include "AudioManager.h"
#include "vld.h"
#include "GameStateExampleGame.h"

using namespace std;


int main()
{
	Game MyGame;
	GameStateExample gameStateMachine(&MyGame);
	MyGame.Initialize(&gameStateMachine);
	MyGame.RunGameLoop();

	AudioManager::DestroyInstance();
	return 0;
}

