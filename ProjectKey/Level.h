#pragma once
#include <string>
class Level
{
public:

	Level();
	~Level();

	bool Load(std::string LevelName, int*PlayerX,int*PlayerY);
	void Draw(int X, int Y);
	bool IsSpace(int X,int Y);
	bool IsDoor(int X,int Y);
	bool IsKey(int X,int Y);
	bool IsGoal(int X,int Y);
	void PickUpKey(int X, int Y);
	void OpenDoor(int X, int Y);
	int	GetHeight() { return M_Height; }
	int	GetWidth() { return M_Width; }
private:
	bool ConvertLevel(int* PlayerX, int* PlayerY);
	int GetIndexFromCoordinates(int X, int Y);
	char* M_pLevelData;
	int	M_Height;
	int	M_Width;
};
