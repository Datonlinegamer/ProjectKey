#pragma once
#include "PlaceableActor.h"
class Money :public PlaceableActor
{
public:
	Money(int X, int Y, int Worth);
	int GetWorth() const { return M_Worth; }
	virtual void Draw()override;
	virtual ActorType GetType() override { return ActorType::Money; }
private:
	int	M_Worth;
};