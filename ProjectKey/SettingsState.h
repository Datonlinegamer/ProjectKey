#pragma once
#include "GameState.h"
class GameStateExample;
class SettingsState : public GameState
{
	GameStateExample* m_Owner;

public:
	SettingsState(GameStateExample* pOwner);
	~SettingsState() = default;
	virtual bool Update(bool processinginput = true)override;
	virtual void Draw() override;
};

