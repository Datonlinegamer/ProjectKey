#include <iostream>
#include <conio.h>
#include <fstream>
#include "LevelEdittor.h"
using namespace std;


LevelEditor level;
constexpr int ArrowInput = 224;
constexpr int LeftArrowInput = 75;
constexpr int RightArrowInput = 77;
constexpr int UpArrowInput = 72;
constexpr int DownArrowInput = 80;
constexpr int KEscape = 27;
constexpr int KBackspace = 8;

constexpr char KCursor = '_';
constexpr char KTopRightBorder = 187;
constexpr char KTopLeftBorder = 201;
constexpr char KBottomRightBorder = 188;
constexpr char KBottomLeftBorder = 200;

constexpr char KHorizontalBorder = 205;
constexpr char KVerticalBorder = 186;

int main()
{
    char* pLevel = nullptr;
    int LevelWidth;
    int LevelHeight;
    bool done = false;
 
    while (!done)
    {
        system("cls");
        std::cout << "Please one of the following options:" << std::endl;
        std::cout << "1. Load Level" << std::endl;
        std::cout << "2. New Level" << std::endl;
        std::cout << "3. Quit" << std::endl;

        int input;
        std::cin >> input;
        if (input == 1)
        {
            //Load level
            std::cout << "Enter Level name";
            string levelName;
            std::cin >> levelName;
            levelName.insert(0, "../");
            ifstream levelfile;
            levelfile.open(levelName);
            if (!levelfile)
            {
                std::cout << "Opening file failed!" << std::endl;
            }
            else
            {
                constexpr int tempSize = 25;
                char temp[tempSize];

                levelfile.getline(temp, tempSize, '\n');
                LevelWidth = atoi(temp);

                levelfile.getline(temp, tempSize, '\n');
                LevelHeight = atoi(temp);
                pLevel = new char[LevelWidth * LevelHeight];
                levelfile.read(pLevel, LevelWidth * LevelHeight);
                levelfile.close();
               level.RunEditor(pLevel, LevelWidth, LevelHeight);

                delete[] pLevel;
                pLevel = nullptr;
            }
        }
        else if (input == 2)
        {
            //New level
            level.GetLevelDimension(LevelWidth, LevelHeight);
            pLevel = new char[LevelWidth * LevelHeight];

            for (int i = 0; i < LevelWidth * LevelHeight; i++)
            {
                pLevel[i] = ' ';
            }
            level.RunEditor(pLevel, LevelWidth, LevelHeight);

            delete[] pLevel;
            pLevel = nullptr;
        }
        else
        {
            done = true;
        }
    }
}

 void LevelEditor:: RunEditor(char* PLevel, int width, int height)
{


    int CursorX = 0;
    int CursorY = 0;
    bool doneEditing = false;
    while (!doneEditing)
    {
        system("cls");
      level.DisplayLevel(PLevel, width, height, CursorX, CursorY);
        level.DisplayLegend();
        doneEditing = level.EditLevel(PLevel, CursorX, CursorY, height, width);
    }
   level.SaveLevel(PLevel, width, height);
    system("cls");
   level. DisplayLevel(PLevel, width, height, -1, -1);
   
   
}


void LevelEditor::DisplayLegend()
{
    cout << "Arrow to move cursor" << endl;
    cout << "ESC to finish editing" << endl;
    cout << "+ | - for walls" << endl;
    cout << "@ for player start" << endl;
    cout << "rgb for key " << endl;
    cout << "RGB for door " << endl;
    cout << "$ for money" << endl;
    cout << "v for verticcal moving enemys" << endl;
    cout << "h for horizontal moving enemys" << endl;
    cout << "e for non moving enemys" << endl;
    cout << "x for end" << endl;


}


void LevelEditor:: SaveLevel(char* Plevel, int Width, int Height)
{
    cout << "Pick a name for your level file (eg: Level1.txt):";
    string LevelName;
    cin >> LevelName;
    LevelName.insert(0, "../");

    ofstream Levelfile;
    Levelfile.open(LevelName);
    if (!Levelfile)
    {
        cout << "Opening file faild!" << endl;
    }
    else
    {
        Levelfile << Width << endl;
        Levelfile << Height << endl;
        Levelfile.write(Plevel, Width * Height);
        if (!Levelfile)
        {
            cout << "Write faild!" << endl;
        }
        Levelfile.close();
    }
}

bool LevelEditor:: EditLevel(char* PLevel, int& CursorX, int& CursorY, int Height, int Width)
{
    int NewCursorX = CursorX;
    int NewCursorY = CursorY;

    int Input = _getch();

    if (Input == ArrowInput)
    {
        int ArrowKey = _getch();
        switch (ArrowKey)
        {
        case LeftArrowInput:
            NewCursorX--;
            break;
        case RightArrowInput:
            NewCursorX++;
            break;
        case UpArrowInput:
            NewCursorY--;
            break;
        case DownArrowInput:
            NewCursorY++;
            break;
        }

        if (NewCursorX < 0)
        {
            NewCursorX = 0;
        }
        else if (NewCursorX >= Width)
        {
            NewCursorX = Width - 1;
        }

        if (NewCursorY < 0)
        {
            NewCursorY = 0;
        }
        else if (NewCursorY >= Height)
        {
            NewCursorY = Height - 1;
        }

        CursorX = NewCursorX;
        CursorY = NewCursorY;
    }
    else
    {
        if (Input == KEscape)
        {
            return true;
        }
        else if(Input == KBackspace)
        {
            cin.ignore();

        }
        else
        {
            int Index = GetIndexFromXY(NewCursorX, NewCursorY, Width);
            PLevel[Index] = (char)Input;
        }
    }
    return false;
}

void LevelEditor::GetLevelDimension(int& Width, int& Height)
{
    cout << "Enter the width of your level: ";
    cin >> Width;
    cout << "Enter the height of your level: ";
    cin >> Height;
}

 void LevelEditor::DisplayLevel(char* plevel, int Width, int Height, int CursorX, int CursorY)
{
   level.DisplayTopBorder(Width);
    for (int Y = 0; Y < Height; Y++)
    {
        level.DisplayLeftBorder();
      
        for (int X = 0; X < Width; X++)
        {
            if (CursorX == X && CursorY == Y)
            {
                cout << KCursor;
            }
            else
            {
                int Index = level.GetIndexFromXY(X, Y, Width);
                cout << plevel[Index];
            }
        }
        level.DisplayRightBorder();
    }
   level. DisplayBottomBorder(Width);
}

int LevelEditor:: GetIndexFromXY(int X, int Y, int Width)
{
    return X + Y * Width;
}

void LevelEditor:: DisplayTopBorder(int width)
{
    cout << KTopLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << KHorizontalBorder;
    }
    cout << KTopRightBorder << endl;
}

 void LevelEditor::DisplayBottomBorder(int width)
{
    cout << KBottomLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << KHorizontalBorder;
    }
    cout << KBottomRightBorder << endl;
}

void LevelEditor:: DisplayLeftBorder()
{
    cout << KVerticalBorder;
}

void LevelEditor:: DisplayRightBorder()
{
    cout << KVerticalBorder << endl;
}
