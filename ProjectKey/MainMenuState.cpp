#include "MainMenuState.h"

#include <iostream>
#include<conio.h>
#include "GameStateExampleGame.h"


constexpr int kEscapeKey = 27;
constexpr char  kPlay = '1';
constexpr char  khighScore = '2';
constexpr char kSetting = '3';
constexpr char  kQuit = '4';

MainMenuState::MainMenuState(GameStateExample* pOwner)
	:m_Owner(pOwner)
{
}

bool MainMenuState::Update(bool processinginput)
{
	bool shouldQuit = false;

	if (processinginput)
	{
		int input = _getch();

		if (input == kEscapeKey || (char)input == kQuit)
		{
			shouldQuit = true;
		}
		else if((char)input ==kPlay)
		{
			m_Owner->LoadScene(GameStateExample::SceneName::Gameplay);
		}

		else if ((char)input == khighScore)
		{
			m_Owner->LoadScene(GameStateExample::SceneName::HighScore);
		}

		else if ((char)input == kSetting)
		{
			m_Owner->LoadScene(GameStateExample::SceneName::Setting);
		}

	}
	return shouldQuit;
}

void MainMenuState::Draw()
{
	system("cls");
	std::cout << std::endl << std::endl << std::endl;	

	std::cout << "   ----- MainMenu ------" << std::endl << std::endl;

	std::cout << "          " << kPlay << "Play" << std::endl;
	std::cout << "          " << khighScore << "Highscore" << std::endl;
	std::cout << "          " << kSetting << "Settings" << std::endl;
	std::cout << "          " << kQuit << "Quit" << std::endl;
}

