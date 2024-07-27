#pragma once
#include <string>
#include <vector>
class PlaceableActor;
class Player;
class Level
{
public:

	Level();
	~Level();

	bool Load(std::string LevelName, int*PlayerX,int*PlayerY);
	void Draw();
	bool IsSpace(int X,int Y);
	bool IsWall(int X,int Y);
	int	GetHeight() { return M_Height; }
	int	GetWidth() { return M_Width; }
	PlaceableActor* UpdateActors(int X, int Y);
	static constexpr char Wall = (char)219;
private:
	bool ConvertLevel(int* PlayerX, int* PlayerY);
	int GetIndexFromCoordinates(int X, int Y);
	char* M_pLevelData;
	int	M_Height;
	int	M_Width;
	std::vector<PlaceableActor*> M_pActors;
};
