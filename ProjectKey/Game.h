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
	bool DidUserQuit() { return M_UserQuit; }
	int GetPlayerlives() { return M_Player.GetLives(); }
private:
	bool M_UserQuit;
	Player	M_Player;
	Level M_Level;
	bool M_GameOver;
	bool Update();
	void Draw();
	bool HandleCollison(int NewPlayerX, int NewPlayerY);
};