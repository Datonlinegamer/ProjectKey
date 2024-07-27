#pragma once
#include "Point.h"


enum class ActorColor
{
	KRegulerColor = 7,
	KColorBlue = 9,
	KGreenColor = 10,
	KRedColor = 12,
	KGreenColorSolid = 34,
	KRedColorSoild = 68,
	KColorBlueSoild = 153,
 
};
enum class ActorType
{
	Door,
	Enemy,
	Goal,
	Key,
	Money,
	Player	
};

class PlaceableActor	
{
public:
	PlaceableActor(int X, int Y, ActorColor Color = ActorColor::KRegulerColor);
	virtual ~PlaceableActor();

	int GetXPosition();
	int GetYPosition();
	int* GetXPositionPointer();
	int* GetYPositionPointer();
	void SetPosition(int X,int Y);

	ActorColor GetColor() { return M_Color; }
	bool Remove() { return M_isActive = false; }

	bool IsActive() { return M_isActive; }
	void Place(int X, int Y);
	virtual  ActorType GetType() = 0;
	virtual void Draw() = 0;
	virtual void Update()
	{

	}

protected:
	Point* M_pPosition;
	bool M_isActive;
	ActorColor M_Color;
};