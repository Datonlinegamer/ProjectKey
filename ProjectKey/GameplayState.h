#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"
#include <Windows.h>
class GameStateExample;

class GameplayState : public GameState
{
	GameStateExample* m_pOwner;
	Player	m_Player;
	Level* m_pLevel;

	
	bool m_BeatLevel;
	int m_SkipFrameCount;
	static constexpr int kFramesToSkip = 2;

	int m_currnentLevel;
	std::vector<std::string> m_LevelNames;

public:
	GameplayState(GameStateExample* pOwner);
	~GameplayState();
	virtual void Enter()override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;


private:
	bool Load();
	bool HandleCollison(int NewPlayerX, int NewPlayerY);
	void DrawHud(const HANDLE& console);
};

