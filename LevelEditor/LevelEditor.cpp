#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;

void GetLevelDimension(int& Width, int& Height);
void DisplayLevel(char* plevel, int width, int height, int CursorX, int CursorY);
void DisplayTopBorder(int width);
void DisplayBottomBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();
void SaveLevel(char* Plevel, int Width, int Height);
void DisplayLegend();
int GetIndexFromXY(int X, int Y, int Width);
bool EditLevel(char* PLevel, int& CursorX, int& CursorY, int Height, int Width);


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
    int LevelWidth;
    int LevelHeight;
    GetLevelDimension(LevelWidth, LevelHeight);

    char* PLevel = new char[LevelWidth * LevelHeight];

    for (int i = 0; i < LevelWidth * LevelHeight; i++)
    {
        PLevel[i] = ' ';
    }

    int CursorX = 0;
    int CursorY = 0;
    bool DoneEditing = false;
    while (!DoneEditing)
    {
        system("cls");
        DisplayLevel(PLevel, LevelWidth, LevelHeight, CursorX, CursorY);
        DisplayLegend();
        DoneEditing = EditLevel(PLevel, CursorX, CursorY, LevelHeight, LevelWidth);
    }
    SaveLevel(PLevel, LevelWidth, LevelHeight);
    system("cls");
    DisplayLevel(PLevel, LevelWidth, LevelHeight, -1, -1);
    delete[] PLevel;
    PLevel = nullptr;
    return 0;
}


void DisplayLegend()
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


void SaveLevel(char* Plevel, int Width, int Height)
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

bool EditLevel(char* PLevel, int& CursorX, int& CursorY, int Height, int Width)
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

void GetLevelDimension(int& Width, int& Height)
{
    cout << "Enter the width of your level: ";
    cin >> Width;
    cout << "Enter the height of your level: ";
    cin >> Height;
}

void DisplayLevel(char* plevel, int Width, int Height, int CursorX, int CursorY)
{
    DisplayTopBorder(Width);
    for (int Y = 0; Y < Height; Y++)
    {
        DisplayLeftBorder();
        for (int X = 0; X < Width; X++)
        {
            if (CursorX == X && CursorY == Y)
            {
                cout << KCursor;
            }
            else
            {
                int Index = GetIndexFromXY(X, Y, Width);
                cout << plevel[Index];
            }
        }
        DisplayRightBorder();
    }
    DisplayBottomBorder(Width);
}

int GetIndexFromXY(int X, int Y, int Width)
{
    return X + Y * Width;
}

void DisplayTopBorder(int width)
{
    cout << KTopLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << KHorizontalBorder;
    }
    cout << KTopRightBorder << endl;
}

void DisplayBottomBorder(int width)
{
    cout << KBottomLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << KHorizontalBorder;
    }
    cout << KBottomRightBorder << endl;
}

void DisplayLeftBorder()
{
    cout << KVerticalBorder;
}

void DisplayRightBorder()
{
    cout << KVerticalBorder << endl;
}
