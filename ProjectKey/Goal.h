#pragma once
#include "PlaceableActor.h"
class Goal :public PlaceableActor
{
public:
	Goal(int X, int Y);

	virtual void Draw();
};
