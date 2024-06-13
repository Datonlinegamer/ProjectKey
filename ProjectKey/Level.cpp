#include "Level.h"
#include <iostream>
#include <fstream>
using namespace std;
constexpr char Wall = (char) 219;
constexpr char Key = (char)232;
constexpr char Door =(char) 179;
constexpr char Goal= (char) 36;

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

void Level::Draw(int X, int Y)
{
    int Index = GetIndexFromCoordinates(X, Y);
    cout << M_pLevelData[Index];

}

bool Level::IsSpace(int X, int Y)
{

	return M_pLevelData[GetIndexFromCoordinates(X,Y)] == ' ';
}

bool Level::IsDoor(int X, int Y)
{
	return M_pLevelData[GetIndexFromCoordinates(X,Y)] == Door;
	
}

bool Level::IsKey(int X, int Y)
{

	return M_pLevelData[GetIndexFromCoordinates(X, Y)] == Key;
    
}

bool Level::IsGoal(int X, int Y)
{
	return M_pLevelData[GetIndexFromCoordinates(X, Y)] == Goal;
}

void Level::PickUpKey(int X, int Y)
{

    M_pLevelData[GetIndexFromCoordinates(X, Y)] = ' ';
     cout << "Collected Key!";
}

void Level::OpenDoor(int X, int Y)
{
    M_pLevelData[GetIndexFromCoordinates(X, Y)] = ' ';
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
            case 'k':
                M_pLevelData[Index] = Key;
                break;

            case 'D':
               M_pLevelData[Index] = Door;
                break;
            case 'X':
                M_pLevelData[Index] = Goal;
                break;

            case '@':
               M_pLevelData[Index] = ' ';
               if (PlayerX != nullptr && PlayerY !=nullptr)
               {
                *PlayerX = X;
                *PlayerY = Y;
               }
                break;
            case ' ':
                break;
                cout << "Invald character in level file" << M_pLevelData[Index] << endl;
                AnyWarnings = true;
            default:
                break;
            }
        }
    }

    return AnyWarnings;

	return false;
}

int Level::GetIndexFromCoordinates(int X, int Y)
{
    return X + Y * M_Width;
}
