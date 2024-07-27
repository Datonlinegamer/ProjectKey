#pragma once
#include "PlaceableActor.h"
class Key : public PlaceableActor
{
public:
	Key(int X, int Y, ActorColor Color)
		:PlaceableActor(X,Y ,Color)
	{

	}
	virtual ActorType GetType() override { return ActorType::Key; }
	virtual void Draw() override;

};
