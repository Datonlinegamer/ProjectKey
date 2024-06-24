#include "Game.h"
#include <iostream>
#include<Windows.h>
#include <conio.h>


#include "Level.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"                                                                                          

using namespace std;

constexpr int KArrowInput = 224;
constexpr int KLeftArrow = 75;
constexpr int KRightArrow = 77;
constexpr int KUpArrow = 72;
constexpr int KDownArrow = 80;
constexpr int KEscapeKey = 27;


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
   char Input = _getch();
    int ArrowInput = 0;
    int NewPlayerX = M_Player.GetXPosition();
    int NewPlayerY = M_Player.GetYPosition();

    if (Input == KArrowInput)
    {
        ArrowInput = _getch();
    }

    if ((Input == KArrowInput && ArrowInput == KLeftArrow) ||
        (char)Input == 'A' || (char)Input == 'a')
    {
        NewPlayerX--;
      
    }
    else if ((Input == KArrowInput && ArrowInput == KRightArrow) ||
        (char)Input == 'D' || (char)Input == 'd')
    {
        NewPlayerX++;
     
    }
    else if ((Input == KArrowInput && ArrowInput == KUpArrow) ||
        (char)Input == 'W' || (char)Input == 'w')
    {
        NewPlayerY--;
       
    }
    else if ((Input == KArrowInput && ArrowInput == KDownArrow) ||
        (char)Input == 'S' || (char)Input == 's')
    {
        NewPlayerY++;
    }
    else if (Input == KEscapeKey)
    {
        M_UserQuit = true;
        return true;
    }
    else if ((char)Input == 'Z' || (char)Input == 'z')
    {
        M_Player.DropKey();
    }

    if (NewPlayerX == M_Player.GetXPosition() && NewPlayerY == M_Player.GetYPosition())
    {
        return false;
    }
    else
    {
    
        return HandleCollison(NewPlayerX, NewPlayerY);
    }

}



bool Game::HandleCollison(int NewPlayerX, int NewPlayerY)
{
    PlaceableActor* CollidedActor = M_Level.UpdateActors(NewPlayerX, NewPlayerY);

    if (CollidedActor != nullptr && CollidedActor->IsActive())
    {
        Enemy* CollidedEnemy = dynamic_cast<Enemy*>(CollidedActor);
        if (CollidedEnemy)
        {
            CollidedEnemy->Remove();
            M_Player.DecrementLives();
            M_Player.SetPosition(NewPlayerX, NewPlayerY);
            if (M_Player.GetLives() < 0)
            {
                return true;
            }
        }

        Money* CollidedMoney = dynamic_cast<Money*>(CollidedActor);
        if (CollidedMoney)
        {
            CollidedMoney->Remove();
            M_Player.AddMoney(CollidedMoney->GetWorth());
            M_Player.SetPosition(NewPlayerX, NewPlayerY);
        }

        Key* CollidedKey = dynamic_cast<Key*>(CollidedActor);
        if (CollidedKey)
        {
            if (!M_Player.HasKey())
            {
                M_Player.PickUpKeyInLevel(CollidedKey);
                CollidedKey->Remove();
                M_Player.SetPosition(NewPlayerX, NewPlayerY);
                // PlayKeySound
            }
        }

        Door* CollidedDoor = dynamic_cast<Door*>(CollidedActor);
        if (CollidedDoor)
        {
            if (!CollidedDoor->IsDoorOpen())
            {
                if (M_Player.HasKey(CollidedDoor->GetColor()))
                {
                    CollidedDoor->Open();
                    CollidedDoor->Remove();
                    M_Player.UseKey();
                    M_Player.SetPosition(NewPlayerX, NewPlayerY);
                    // PlayDoorSound
                }
                else
                {
                    // CloseDoorSound
                    return false;
                }
            }
        }

        Goal* CollidedGoal = dynamic_cast<Goal*>(CollidedActor);
        if (CollidedGoal)
        {
            CollidedGoal->Remove();
            M_Player.SetPosition(NewPlayerX, NewPlayerY);
            return true;
        }
    }

    if (M_Level.IsSpace(NewPlayerX, NewPlayerY) ||
        (CollidedActor != nullptr && dynamic_cast<Door*>(CollidedActor) && dynamic_cast<Door*>(CollidedActor)->IsDoorOpen()))
    {
        M_Player.SetPosition(NewPlayerX, NewPlayerY);
    }
    else if(M_Level.IsWall(NewPlayerY,NewPlayerY))
    {

    }
    return false;
}




void Game::Draw()
{
   
    HANDLE  Console = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    M_Level.Draw();     
 
    COORD ActorCursorPosition;
    ActorCursorPosition.X = M_Player.GetXPosition();
    ActorCursorPosition.Y = M_Player.GetYPosition();
    SetConsoleCursorPosition(Console, ActorCursorPosition);

    M_Player.Draw();
    COORD CurrentCursorPosition;
    CurrentCursorPosition.X = 0;
    CurrentCursorPosition.Y = M_Level.GetHeight();
    SetConsoleCursorPosition(Console, CurrentCursorPosition);
    
    

       
    
}

