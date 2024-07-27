#include "GameplayState.h"
#include <iostream>
#include<Windows.h>
#include <conio.h>


#include "Level.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"                                                                                          
#include <cassert>
#include "Utility.h"
#include "AudioManager.h"
#include "GameStateExampleGame.h"


using namespace std;


constexpr int KArrowInput = 224;
constexpr int KLeftArrow = 75;
constexpr int KRightArrow = 77;
constexpr int KUpArrow = 72;
constexpr int KDownArrow = 80;
constexpr int KEscapeKey = 27;

GameplayState::GameplayState(GameStateExample* pOwner)
	: m_pOwner(pOwner)
	,m_BeatLevel(false)
    ,m_SkipFrameCount(0)
    ,m_currnentLevel(0)
    ,m_pLevel(nullptr)
	
{
    m_LevelNames.push_back("Level1.txt");
    m_LevelNames.push_back("Level2.txt");
    m_LevelNames.push_back("Level3.txt");
}


GameplayState::~GameplayState()
{
    delete m_pLevel;
    m_pLevel = nullptr;
}


bool GameplayState::Load()
{

    if (m_pLevel)
    {
        delete m_pLevel;
        m_pLevel = nullptr;
    }

    m_pLevel = new Level;
	return m_pLevel->Load(m_LevelNames.at(m_currnentLevel), m_Player.GetXPositionPointer(), m_Player.GetYPositionPointer());

}

void GameplayState::Enter()
{
	Load();
}

bool GameplayState::Update(bool processInput)
{
    if (processInput && !m_BeatLevel)
    {
      char Input = _getch();
        int ArrowInput = 0;
        int NewPlayerX = m_Player.GetXPosition();
        int NewPlayerY = m_Player.GetYPosition();

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
            m_pOwner->LoadScene(GameStateExample::SceneName::Mainmenu);
        }
        else if ((char)Input == 'Z' || (char)Input == 'z')
        {
            m_Player.DropKey();
        }

        if (NewPlayerX == m_Player.GetXPosition() && NewPlayerY == m_Player.GetYPosition())
        {
           
        }
        else
        {

             HandleCollison(NewPlayerX, NewPlayerY);
        }     
    }

    if (m_BeatLevel)
    {
        ++m_SkipFrameCount;
        if (m_SkipFrameCount > kFramesToSkip)
        {
            m_BeatLevel = false;
            m_SkipFrameCount = 0;
            ++m_currnentLevel;
            if (m_currnentLevel == m_LevelNames.size())
            {
                Utility::writeHightScore(m_Player.GetMoney());
                AudioManager::GetInstance()->PlayWinSound();
                m_pOwner->LoadScene(GameStateExample::SceneName::Win);
            }
            else
            {
                Load();
            }
           
        }
    }
    return false;
  
}

bool GameplayState::HandleCollison(int NewPlayerX, int NewPlayerY)
{
    bool isGameDone = false;
    PlaceableActor* CollidedActor = m_pLevel->UpdateActors(NewPlayerX, NewPlayerY);

    if (CollidedActor != nullptr && CollidedActor->IsActive())
    {

        switch (CollidedActor->GetType())
        {
        case ActorType::Enemy:
        {
            Enemy* CollidedEnemy = dynamic_cast<Enemy*>(CollidedActor);
            assert(CollidedEnemy);
            AudioManager::GetInstance()->PlayLoseLivesSound();
            CollidedEnemy->Remove();
            m_Player.DecrementLives();
            m_Player.SetPosition(NewPlayerX, NewPlayerY);
            if (m_Player.GetLives() < 0)
            {
                AudioManager::GetInstance()->PlayLoseLivesSound();
                m_pOwner->LoadScene(GameStateExample::SceneName::Lose);
            }
            break;
        }



        case ActorType::Money:
        {

            Money* CollidedMoney = dynamic_cast<Money*>(CollidedActor);
            assert(CollidedMoney);
            AudioManager::GetInstance()->PlayMoneySound();
            CollidedMoney->Remove();
            m_Player.AddMoney(CollidedMoney->GetWorth());
            m_Player.SetPosition(NewPlayerX, NewPlayerY);
            break;
        }


        case ActorType::Key:
        {
            Key* CollidedKey = dynamic_cast<Key*>(CollidedActor);
            assert(CollidedKey);

            if (!m_Player.HasKey())
            {
                m_Player.PickUpKeyInLevel(CollidedKey);
                CollidedKey->Remove();
                m_Player.SetPosition(NewPlayerX, NewPlayerY);
                AudioManager::GetInstance()->PlayKeyPickUpSound();
            }
            break;
        }
        case ActorType::Door:
        {
            Door* CollidedDoor = dynamic_cast<Door*>(CollidedActor);
            assert(CollidedDoor);

            if (!CollidedDoor->IsDoorOpen())
            {
                if (m_Player.HasKey(CollidedDoor->GetColor()))
                {
                    CollidedDoor->Open();
                    CollidedDoor->Remove();
                    m_Player.UseKey();
                    m_Player.SetPosition(NewPlayerX, NewPlayerY);
                    AudioManager::GetInstance()->PlayDoorOpenSound();
                }
                else
                {
                    AudioManager::GetInstance()->PlayDoorClosedSound();
                    return false;
                }
                break;
            }
        }


        case ActorType::Goal:
        {


            Goal* CollidedGoal = dynamic_cast<Goal*>(CollidedActor);
            assert(CollidedGoal);

            CollidedGoal->Remove();
            m_Player.SetPosition(NewPlayerX, NewPlayerY);
            m_BeatLevel = true;
            break;
        }

        default:
            break;
        }

    }

    if (m_pLevel->IsSpace(NewPlayerX, NewPlayerY) ||
        (CollidedActor != nullptr && dynamic_cast<Door*>(CollidedActor) && dynamic_cast<Door*>(CollidedActor)->IsDoorOpen()))
    {
        m_Player.SetPosition(NewPlayerX, NewPlayerY);
    }
    else if (m_pLevel->IsWall(NewPlayerY, NewPlayerY))
    {

    }
}

void GameplayState::Draw()
{

    HANDLE  Console = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    m_pLevel->Draw();

    COORD ActorCursorPosition;
    ActorCursorPosition.X = m_Player.GetXPosition();
    ActorCursorPosition.Y = m_Player.GetYPosition();
    SetConsoleCursorPosition(Console, ActorCursorPosition);

    m_Player.Draw();
    COORD CurrentCursorPosition;
    CurrentCursorPosition.X = 0;
    CurrentCursorPosition.Y = m_pLevel->GetHeight();
    SetConsoleCursorPosition(Console, CurrentCursorPosition);
    DrawHud(Console);
}

void GameplayState:: DrawHud(const HANDLE& console)
{
    std::cout << std::endl;

    for (int i = 0;  i < m_pLevel->GetWidth();  i++)
    {
        std::cout << Level::Wall;
    }
    std::cout << std::endl;

    std::cout << Level::Wall;

    std::cout << "wasd-move" << Level::Wall << "z-drop key" << Level::Wall;
    std::cout << "$:" << m_Player.GetMoney() << " " << Level::Wall;
    std::cout << "lives:" << m_Player.GetLives() << " " << Level::Wall;
    std::cout << "key:";

    if (m_Player.HasKey())
    {
        m_Player.GetKey()->Draw();
    }
    else
    {
        std::cout << " ";
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    COORD pos;
    pos.X = m_pLevel->GetWidth() - 1;
    pos.Y = csbi.dwCursorPosition.Y;
    SetConsoleCursorPosition(console, pos);

    std::cout << Level::Wall;
    std::cout << std::endl;





    for (int i = 0; i < m_pLevel->GetWidth(); i++)
    {
        std::cout << Level::Wall;
    }
    std::cout << std::endl;
}

