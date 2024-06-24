#pragma once
#include "Point.h"
constexpr int KGreenColor = 10;
constexpr int KGreenColorSolid = 34;
constexpr int KRedColor = 12;
constexpr int KRedColorSoild = 68;
constexpr int KColorBlue = 9;
constexpr int KColorBlueSoild = 153;
constexpr int KRegulerColor = 7;

class PlaceableActor	
{
public:
	PlaceableActor(int X, int Y, int Color = KRegulerColor);
	virtual ~PlaceableActor();

	int GetXPosition();
	int GetYPosition();
	int* GetXPositionPointer();
	int* GetYPositionPointer();
	void SetPosition(int X,int Y);

	int GetColor() { return M_Color; }
	bool Remove() { return M_isActive = false; }

	bool IsActive() { return M_isActive; }
	void Place(int X, int Y);
	virtual void Draw() = 0;
	virtual void Update()
	{

	}

protected:
	Point* M_pPosition;
	bool M_isActive;
	int M_Color;
};