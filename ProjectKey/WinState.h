#pragma once
#include "GameState.h"
class GameStateExample;
class WinState : public GameState
{
	GameStateExample* m_Owner;
public:
	WinState(GameStateExample* pOwner);
	~WinState() = default;
	virtual bool Update(bool processinginput = true)override;
	virtual void Draw()override;
};

