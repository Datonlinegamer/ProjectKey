#pragma once
#include "PlaceableActor.h"
class Goal :public PlaceableActor
{
public:
	virtual ActorType GetType() override { return ActorType::Goal; }
	Goal(int X, int Y);

	virtual void Draw();
};
