#pragma once
#include "PlaceableActor.h"

class Enemy : public PlaceableActor
{
public:
	Enemy(int X, int Y, int DeltaX = 0, int DeltaY = 0);

	virtual void Draw()override;
	virtual void Update()override;


private:
	int M_MovementInX;
	int M_MovementInY;

	int	M_CurrentMovementX;
	int	M_CurrentMovementY;

	int M_DirectionX;
	int M_DirectionY;

	void UpdateDirection(int& Current, int& Direction, int& Movement);

};
