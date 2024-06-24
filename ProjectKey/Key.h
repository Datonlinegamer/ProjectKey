#pragma once
#include "PlaceableActor.h"
class Key : public PlaceableActor
{
public:
	Key(int X, int Y, int Color)
		:PlaceableActor(X,Y ,Color)
	{

	}

	virtual void Draw() override;

};
