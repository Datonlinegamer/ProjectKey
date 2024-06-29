#include "Level.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include "Player.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"
#include <cassert>
#include "Level.h"

using namespace std;
constexpr char Wall = (char) 219;

Level::Level() :M_pLevelData{nullptr},M_Width{0},M_Height{0}
{
}

Level::~Level()
{
	if (M_pLevelData != nullptr)
	{
		delete[] M_pLevelData;
		M_pLevelData = nullptr;
	}
    while (M_pActors.empty())
    {
        delete M_pActors.back();
        M_pActors.pop_back();
    }
}

bool Level::Load(std::string LevelName, int* PlayerX, int* PlayerY)
{
    LevelName.insert(0, "../");
    ifstream Levelfile;
    Levelfile.open(LevelName);
    if (!Levelfile)
    {
        cout << "Opening file failed" << endl;
        return false;
    }
    else
    {
        const int TempSize = 25;
        char Temp[TempSize];
        Levelfile.getline(Temp, TempSize, '\n');
       M_Width = atoi(Temp);

        Levelfile.getline(Temp, TempSize, '\n');
        M_Height = atoi(Temp);

        M_pLevelData = new char[M_Width * M_Height];
        Levelfile.read(M_pLevelData,(long long) M_Width *(long long) M_Height);
       

        bool AnyWarnings = ConvertLevel(PlayerX,PlayerY);
        if (AnyWarnings)
        {
            cout << "There were some warnings in the level data see above." << endl;
            system("Pause");
        }
	    return true;
    }
}

void Level::Draw()
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Console, KRegulerColor);

    for (int Y = 0; Y < GetHeight(); Y++)
    {
        for (int X = 0; X < GetWidth(); X++)
        {
            int IndexToPoint = GetIndexFromCoordinates(X, Y);
            cout << M_pLevelData[IndexToPoint];

        }
        cout << endl;
    }

    COORD ActorCurosPosition;

    for (auto Actor = M_pActors.begin(); Actor != M_pActors.end(); ++Actor)
    {
        if ((*Actor)->IsActive())
        {
            ActorCurosPosition.X = (*Actor)->GetXPosition();
            ActorCurosPosition.Y = (*Actor)->GetYPosition();
            SetConsoleCursorPosition(Console, ActorCurosPosition);
            (*Actor)->Draw();
        }
    }
}

bool Level::IsSpace(int X, int Y)
{

	return M_pLevelData[GetIndexFromCoordinates(X,Y)] ==     ' ';
}

bool Level::IsWall(int X, int Y)
{
    return M_pLevelData[GetIndexFromCoordinates(X, Y)] == Wall;
}


bool Level::ConvertLevel(int* PlayerX, int* PlayerY)
{
    bool AnyWarnings = false;

    for (int Y = 0; Y < M_Height; Y++)
    {
        for (int X = 0; X < M_Width; X++)
        {
            int Index = GetIndexFromCoordinates(X, Y);
            switch (M_pLevelData[Index])
            {       
            case '+':
            case '_':
            case '|':
                M_pLevelData[Index] = Wall;
                break;

            case 'r':
                M_pLevelData[Index] = ' ';
                M_pActors.push_back(new Key(X, Y, KRedColor));
               
                break;

            case 'g':
                M_pLevelData[Index] = ' ';
                M_pActors.push_back(new Key(X, Y, KGreenColor));
                break;

            case 'b':
                M_pLevelData[Index] = ' ';
                M_pActors.push_back(new Key(X, Y, KColorBlue));
                break;


            case 'R':
                M_pLevelData[Index] = ' ';
                M_pActors.push_back(new Door(X, Y, KRedColor, KRedColorSoild));
                break;

            case 'G':
                M_pLevelData[Index] = ' ';
                M_pActors.push_back(new Door(X, Y, KGreenColor, KGreenColorSolid));
                break;

            case 'B':
                M_pLevelData[Index] = ' ';
                M_pActors.push_back(new Door(X, Y, KColorBlue, KColorBlueSoild));
                break;

            case 'X':
                M_pLevelData[Index] = ' ';
                M_pActors.push_back(new Goal(X, Y));
                break;

            case '$':
                M_pLevelData[Index] = ' ';
                M_pActors.push_back(new Money(X, Y, 1 + rand() % 5));
                break;

            case '@':
                M_pLevelData[Index] = ' ';
                if (PlayerX != nullptr && PlayerY != nullptr)
                {
                    *PlayerX = X;                                                                           
                    *PlayerY = Y;
                    
                }
                break;

            case 'e':
                M_pLevelData[Index] = ' ';
                M_pActors.push_back(new Enemy(X, Y));
                break;

            case 'h':
                M_pLevelData[Index] = ' ';
                M_pActors.push_back(new Enemy(X, Y, 3, 0));
                break;

            case 'v':
                M_pLevelData[Index] = ' ';
                M_pActors.push_back(new Enemy(X, Y, 0, 2));
                break;
                break;
            case ' ':
                
                break;

            default:
                cout << "Invalid character in level file: " << M_pLevelData[Index] << endl;
                AnyWarnings = true;
                break;
            }
        }
    }
    return AnyWarnings;
}


int Level::GetIndexFromCoordinates(int X, int Y)
{
    return X + Y * M_Width;
}

PlaceableActor* Level::UpdateActors(int X, int Y)
{
    PlaceableActor* CollidedActors = nullptr;
    for (auto Actor = M_pActors.begin(); Actor!=M_pActors.end(); ++Actor )
    {
        (*Actor)->Update();
        if (X ==(*Actor)->GetXPosition() && Y== (*Actor)->GetYPosition())
        {
            assert(CollidedActors == nullptr);
            CollidedActors = (*Actor);
        }
    }

    return CollidedActors;
}