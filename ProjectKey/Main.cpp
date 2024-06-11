#include <iostream>
using namespace std;
#include<Windows.h>
#include <conio.h>
#include <fstream>

 const char Player = '@';
 constexpr char Wall = 219;
 constexpr char Key = 232;
 constexpr char Door = 179;
 constexpr char Goal = 36;
 constexpr int OpenDoorcolor = 10;
 constexpr int CloseDoorcolor = 12;
 constexpr int Regularcolor = 7;


int GetIndexFromCoordinates(int X, int Y, int Width);
void DrawLevel(char Level[], int Width, int Height,int Playerx,int Playery,bool PlayerhasKey);
bool UpdatePlayerPosition(char Level[], int& Playerx, int& playery, int Width, bool& PlayHasKey);
char* LoadLevel(string Level, int& Width, int& Height);
bool ConvertLevel(char  Level [], int Width, int Height, int& PlayerX, int& PlayerY);
void PlayCloseDoorSound();
void PlayOpenSound();
void PlayKeySound();
void PlayWinSound();
int main()
{
       int Width = 30;
       int Height = 15;
       char* LevelArray = LoadLevel("Level1.txt", Width, Height);
   



      int PlayerX = 1;
      int PlayerY = 1;
      bool PlayerHasKey = false;
      bool AnyWarnings = ConvertLevel(LevelArray, Width, Height, PlayerX, PlayerY);
      if (AnyWarnings)
      {
          cout << "There were some warnings in the level data see above." << endl;
          system("Pause");
      }
      bool GameOver = false;

      while (!GameOver)
      {
            system("cls");
            DrawLevel(LevelArray, Width, Height,PlayerX,PlayerY,PlayerHasKey);
            GameOver = UpdatePlayerPosition( LevelArray, PlayerX,PlayerY, Width,PlayerHasKey);
      }

      system("cls");
      DrawLevel(LevelArray, Width, Height, PlayerX, PlayerY,PlayerHasKey);
      cout << "You Won!" << endl;
      PlayWinSound();


      delete[] LevelArray;
}

char* LoadLevel(string Level, int& Width, int& Height)
{
    Level.insert(0,"../");
    ifstream Levelfile;
    Levelfile.open(Level);
    if (!Levelfile)
    {
        cout << "Opening file failed" << endl;
        return nullptr;
    }
    else
    {
        const int TempSize = 25;
        char Temp[TempSize];
        Levelfile.getline(Temp,TempSize,'\n');
        Width = atoi(Temp);
        
        Levelfile.getline(Temp,TempSize,'\n');
        Height = atoi(Temp);

        char* LevelData = new char[Width * Height];
        Levelfile.read(LevelData, Width * Height);
        return LevelData;
    }
}
bool ConvertLevel(char* Level, int Width, int Height, int& PlayerX, int& PlayerY)
{
    bool AnyWarnings = false;
    for (int Y= 0; Y < Height; Y++)
    {
        for (int X = 0; X < Width; X++)
        {
            int Index = GetIndexFromCoordinates(X, Y, Width);

            switch (Level[Index])
            {
            case '+':

            case '_':

            case '|':
                 Level[Index] = Wall;
                 break;
            case 'K':
                Level[Index] = Key;
                break;

            case 'D':
                Level[Index] == Door;
                break;
            case 'X':
                Level[Index] == Goal;
                break;

            case '@':
                Level[Index] = ' ';

                PlayerX = X;
                PlayerY = Y;
                break;
                cout << "Invald character in level file" << Level[Index] << endl;
                AnyWarnings = true;
            default:
                break;
            }
        }
    }

    return AnyWarnings;

}

int GetIndexFromCoordinates(int X, int Y, int Width)
{
    return X + Y * Width;
}

void DrawLevel(char Level[], int Width, int Height ,int Playerx,int playery , bool PlayerhasKey) 
{
    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            if (Playerx==x && playery ==y)
            {
                cout << Player << endl;
            }
            else
            {

                int Index = GetIndexFromCoordinates(x, y, Width);
                HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
                if (Level[Index] == 'D')
                {
                    if (PlayerhasKey)
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
                cout << Level[Index];
            }
        }
        cout << endl;
    }
}

bool UpdatePlayerPosition(char Level[], int& Playerx, int& playery,int width, bool& PlayerHasKey)
{
    int NewPlayerX =Playerx;
    int NewPlayerY = playery;
    char Input = _getch();
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
    int Index = GetIndexFromCoordinates(NewPlayerX, NewPlayerY, width);
    if (Level [Index] == ' ')
    {
        Playerx = NewPlayerX;
        playery = NewPlayerY;

    }
    else if (Level[Index] =='k')
    {
        PlayerHasKey = true;
        Level[Index] = ' ';
        PlayKeySound();
        Playerx = NewPlayerX;
        playery = NewPlayerY;

    }
    else if (Level[Index] == 'D'&& PlayerHasKey )
    {
        PlayerHasKey = true;
        Level[Index] = ' ';

        Playerx = NewPlayerX;
        playery = NewPlayerY;
        PlayOpenSound();
    }  
    else if (Level[Index] == 'D'&& !PlayerHasKey)
    {
        PlayCloseDoorSound();
    }
    else if (Level[Index] == 'X' && PlayerHasKey)
    {
        PlayerHasKey = true;
        Level[Index] = ' ';

        Playerx = NewPlayerX;
        playery = NewPlayerY;
        return true;
    }
    return false;
}

void PlayCloseDoorSound()
{
    Beep(500, 75);
    Beep(500, 75);
}

void PlayOpenSound()
{
    Beep(1397, 200);
}

void PlayKeySound()
{
    Beep(1568, 200);
}

void PlayWinSound()
{
    Beep(1568, 200);
    Beep(1568, 200);
    Beep(1568, 200);
    Beep(1245, 1000);
    Beep(1397, 200);
    Beep(1397, 200);
    Beep(1397, 200);
    Beep(1175, 1000);
    
}
