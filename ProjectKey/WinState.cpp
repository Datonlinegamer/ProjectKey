#include "WinState.h"
#include <iostream>
#include<conio.h>
#include "GameStateExampleGame.h"

WinState::WinState(GameStateExample* pOwner)
	:m_Owner(pOwner)
{
}

bool WinState::Update(bool processinginput)
{


	if (processinginput)
	{
		int input = _getch();
		m_Owner->LoadScene(GameStateExample::SceneName::Mainmenu);

	}
	return false;
}

void WinState::Draw()
{
	system("cls");
	std::cout << std::endl << std::endl << std::endl;

	std::cout << "   ----- WELL DONE ------" << std::endl << std::endl;
	std::cout << "         YOU BEAT THE GAME " << std::endl << std::endl;
	std::cout << "         Press any key to go back to the main menu   " << std::endl << std::endl;

}