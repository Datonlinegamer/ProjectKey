#pragma once
class LevelEditor
{
public:


	void GetLevelDimension(int& Width, int& Height);
	void DisplayLevel(char* plevel, int width, int height, int CursorX, int CursorY);
	void DisplayTopBorder(int width);
	void DisplayBottomBorder(int width);
	void DisplayLeftBorder();
	void DisplayRightBorder();
	void SaveLevel(char* Plevel, int Width, int Height);
	void DisplayLegend();
	void RunEditor(char* PLevel,int width ,int height);
	int GetIndexFromXY(int X, int Y, int Width);
	bool EditLevel(char* PLevel, int& CursorX, int& CursorY, int Height, int Width);

};