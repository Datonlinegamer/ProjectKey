#pragma once
#include "PlaceableActor.h"
class Key : public PlaceableActor
{
public:
	Key(int X, int Y, ActorColor Color)
		:PlaceableActor(X,Y ,Color)
	{

	}

	virtual void Draw() override;

};
