#pragma once
#include "GameState.h"
class GameStateExample;
class MainMenuState : public GameState
{
	
public:
	GameStateExample* m_Owner;
	MainMenuState(GameStateExample* pOwner);
	~MainMenuState() = default;
	virtual bool Update(bool processinginput = true)override;
	virtual void Draw()override;
};

