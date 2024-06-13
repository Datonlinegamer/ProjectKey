#pragma once
#include "Player.h"
#include "Level.h"
class Game
{
public:
	Game();
	~Game();
	bool Load();
	void UnLoad();
	void Run();
	bool IsGameOver();
private:
	Player	M_Player;
	Level M_Level;
	bool M_GameOver;
	bool Update();
	void Draw();
};