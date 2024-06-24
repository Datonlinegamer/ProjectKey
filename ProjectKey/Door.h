#pragma once
#include "PlaceableActor.h"
class Door :public PlaceableActor
{
public:
	Door(int X, int Y, int Color, int CloseDoorColor);
	virtual void Draw() override;
	bool IsDoorOpen() { return M_IsOpen; }
	void Open() { M_IsOpen = true; }



private:
	bool M_IsOpen;
	int M_CloseColor;
};
