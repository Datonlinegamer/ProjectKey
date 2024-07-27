#include "LoseState.h"

#include <iostream>
#include<conio.h>
#include "GameStateExampleGame.h"

LoseState::LoseState(GameStateExample* pOwner)
	:m_Owner(pOwner)
{
}

bool LoseState::Update(bool processinginput)
{
	

	if (processinginput)
	{
		int input = _getch();
		m_Owner->LoadScene(GameStateExample::SceneName::Mainmenu);

	}
	return false;
}

void LoseState::Draw()
{
	system("cls");
	std::cout << std::endl << std::endl << std::endl;

	std::cout << "   ----- GAME OVER ------" << std::endl << std::endl;
	std::cout << "         BETTER  LUCK NEXT TIME! " << std::endl << std::endl;
	std::cout << "         Press any key to go back to the main menu " << std::endl << std::endl;

}