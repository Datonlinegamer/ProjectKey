#include "GameStateExampleGame.h"
#include "GameState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "HighScoreState.h"
#include "SettingsState.h"
#include "LoseState.h"
#include "WinState.h"

GameStateExample::GameStateExample(Game* pOwner)
	:m_pOwner(pOwner)
	,m_pCurrentState(nullptr)
	,m_pNewState(nullptr)
{
}

bool GameStateExample::Init()
{
	LoadScene(SceneName::Mainmenu);
	return true;
}

bool GameStateExample::UpdateCurrentState(bool processingInput)
{
	bool done = false;	
	if (m_pNewState != nullptr)
	{
		ChangeState(m_pNewState);
		m_pNewState = nullptr;
	}
	if (m_pCurrentState!= nullptr)
	{
		done = m_pCurrentState->Update(processingInput);
	}
	return done;
}

void GameStateExample::DrawCurrentState()
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Draw();
	}
}

void GameStateExample::ChangeState(GameState* pNewState)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
	}
	delete m_pCurrentState;
	m_pCurrentState = pNewState;
	pNewState->Enter();
}

void GameStateExample::CleanUp()
{
	if (m_pCurrentState)
	{
		m_pCurrentState->Exit();
	}
	delete m_pCurrentState;
}

void GameStateExample::LoadScene(SceneName scene)
{
	switch (scene)
	{
	case SceneName::Mainmenu:
		m_pNewState = new MainMenuState(this);
		break;
	case SceneName::Gameplay:
		m_pNewState = new GameplayState(this);
		break;

	case SceneName::HighScore:
		m_pNewState = new HighScoreState(this);
		break;

	case SceneName::Setting:
		m_pNewState = new SettingsState(this);
		break;
	case SceneName::Win:
		m_pNewState = new WinState(this);
		break;
	case SceneName::Lose:
		m_pNewState = new LoseState(this);
		break;
	default:
		break;
	}
}
