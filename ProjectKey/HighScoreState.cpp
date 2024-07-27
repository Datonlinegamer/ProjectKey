#include "HighScoreState.h"

#include "MainMenuState.h"

#include <iostream>
#include<conio.h>
#include "GameStateExampleGame.h"
#include "Utility.h"


HighScoreState::HighScoreState(GameStateExample* pOwner)
	:m_Owner(pOwner)
{
	m_HighScore = Utility::writeHightScore(0);
}

bool HighScoreState::Update(bool processinginput)
{

	if (processinginput)
	{
		int input = _getch();
		
		m_Owner->LoadScene(GameStateExample::SceneName::Mainmenu);
	}
	return false;
}

void HighScoreState::Draw()
{
	system("cls");
	std::cout << std::endl << std::endl << std::endl;

	std::cout << "   ----- High SCORES ------" << std::endl << std::endl;

	for (auto i = m_HighScore.rbegin(); i != m_HighScore.rend(); ++i)
	{
		std::cout << "                " << *i << std::endl;
	}
	std::cout << "Press any key to go back to the Main Menu" << std::endl << std::endl;
	
}
	