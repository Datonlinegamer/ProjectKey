#pragma once
#include "GameState.h"
#include <set>	
class GameStateExample;
class HighScoreState : public GameState
{
	GameStateExample* m_Owner;
	std::set<int> m_HighScore;
public:
	HighScoreState(GameStateExample* pOwner);
	~HighScoreState() = default;
	virtual bool Update(bool processinginput = true)override;
	virtual void Draw()override;
};

