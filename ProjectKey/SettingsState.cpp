#include "SettingsState.h"

#include "MainMenuState.h"

#include <iostream>
#include<conio.h>
#include "GameStateExampleGame.h"
#include "AudioManager.h"

constexpr int kEscapeKey = 27;
constexpr char  kSound = '1';
constexpr char  kMainMenu= '2';


SettingsState::SettingsState(GameStateExample* pOwner)
	:m_Owner(pOwner)
{
}

bool SettingsState::Update(bool processinginput)
{

	if (processinginput)
	{
		int input = _getch();

		if (input == kEscapeKey || (char)input == kMainMenu)
		{
			m_Owner->LoadScene(GameStateExample::SceneName::Mainmenu);
		}
		else if ((char)input == kSound)
		{
			AudioManager::GetInstance()->ToggleSound();	
			AudioManager::GetInstance()->PlayMoneySound();
		}

	}
	return false;
}

void SettingsState::Draw()
{
	system("cls");
	std::cout << std::endl << std::endl << std::endl;

	std::cout << "   ----- Settings ------" << std::endl << std::endl;

	std::cout << "          " << kSound << "Toggle sound" << std::endl;
	if (AudioManager::GetInstance()->IsSoundOn())
	{
		std::cout << "ON" << std::endl;
	}
	else
	{
		std::cout << "OFF" << std::endl;

	}
	std::cout << "          " << kMainMenu << ". Back to Main Menu" << std::endl;
}