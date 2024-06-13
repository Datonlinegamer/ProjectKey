#include "Game.h"
#include <iostream>
#include<Windows.h>
#include <conio.h>
using namespace std;

constexpr int OpenDoorcolor = 10;
constexpr int CloseDoorcolor = 12;
constexpr int Regularcolor = 7;

Game::Game() :M_GameOver{ false }
{
}

Game::~Game()
{
}

bool Game::Load()
{
	return M_Level.Load("Level1.txt", M_Player.GetXPositionPointer(), M_Player.GetYPositionPointer());
}

void Game::UnLoad()
{
}

void Game::Run()
{
	Draw();
	M_GameOver = Update();

	if (M_GameOver)
	{
		Draw();
	}
}

bool Game::IsGameOver()
{
	return M_GameOver ;
}

bool Game::Update()
{
    char Input = (char)_getch();
    int NewPlayerX = M_Player.GetXPosition();
    int NewPlayerY = M_Player.GetYPosition();
    switch (Input)
    {
    case 'w':
        NewPlayerY--;
        break;
    case's':
        NewPlayerY++;
        break;
    case'a':
        NewPlayerX--;
        break;
    case 'd':
        NewPlayerX++;
        break;
    default:
        break;
    }

    if (M_Level.IsSpace(NewPlayerX,NewPlayerY))
    {
        M_Player.SetPosition(NewPlayerX, NewPlayerY);
    }
    else if (M_Level.IsKey( NewPlayerX,NewPlayerY))
    {
        M_Level.PickUpKey(NewPlayerX, NewPlayerY);
        M_Player.PickUpKeyInLevel();
        M_Player.SetPosition(NewPlayerX, NewPlayerY);   
       
        
       // PlayKeySound();

    }
    else if (M_Level.IsDoor(NewPlayerX,NewPlayerY) && M_Player.HasKey())
    {
        M_Level.OpenDoor(NewPlayerX, NewPlayerY);
        M_Player.UseKey();
        M_Player.SetPosition(NewPlayerX, NewPlayerY);   

        
       // PlayOpenSound();
    }
    else if (M_Level.IsDoor(NewPlayerX, NewPlayerY) && !M_Player.HasKey())
    {
        //PlayCloseDoorSound();
    }
    else if (M_Level.IsGoal(NewPlayerX,NewPlayerY))
    {
        
        M_Player.SetPosition(NewPlayerX, NewPlayerY);   
        
        return true;
    }
   
	return false;
}

void Game::Draw()
{
    system("cls");
    for (int y = 0; y < M_Level.GetHeight(); y++)
    {
        for (int x = 0; x < M_Level.GetWidth(); x++)
        {
            if (M_Player.GetXPosition() == x && M_Player.GetYPosition() == y)
            {
                M_Player.Draw();
            }
            else
            {

                
                HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
                if (M_Level.IsDoor(x,y))
                {
                    if (M_Player.HasKey())  
                    {
                        SetConsoleTextAttribute(Console, OpenDoorcolor);
                    }
                    else
                    {

                        SetConsoleTextAttribute(Console, CloseDoorcolor);
                    }
                }
                else
                {
                    SetConsoleTextAttribute(Console, Regularcolor);

                }
                M_Level.Draw(x, y);
            }
        }
        cout << endl;
    }
}

