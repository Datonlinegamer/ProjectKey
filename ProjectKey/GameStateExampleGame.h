#pragma once
#include "GameStateMachine.h"
class Game;
class GameState;
class GameStateExample : public GameStateMachine
{
public:
	enum class SceneName
	{
		None,
		Mainmenu,
		Gameplay,
		Setting,
		HighScore,
		Lose,
		Win
	};

private:
	Game* m_pOwner;
	GameState* m_pCurrentState;
	GameState* m_pNewState;	


public:

	GameStateExample(Game* pOwner);
	virtual bool Init() override;
	virtual bool UpdateCurrentState(bool processingInput = true)override;
	virtual void DrawCurrentState()override;
	virtual void ChangeState(GameState* pNewState)override;
	virtual void CleanUp();
	void LoadScene(SceneName scene);
};