#pragma once
#include "GameState.h"
class GameStateExample;
class LoseState : public GameState
{
	GameStateExample* m_Owner;
public:
	LoseState(GameStateExample* pOwner);
	~LoseState() = default;
	virtual bool Update(bool processinginput = true)override;
	virtual void Draw()override;
};

