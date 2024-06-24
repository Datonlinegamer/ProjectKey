#include "Enemy.h"
#include<iostream>
Enemy::Enemy(int X, int Y, int DeltaX, int DeltaY):PlaceableActor(X,Y),	 M_CurrentMovementX{0}
,M_CurrentMovementY{0},M_DirectionX{0},	M_DirectionY{0},M_MovementInX{DeltaX},M_MovementInY{DeltaY}
{
	if (M_MovementInX!=0)
	{
		M_DirectionX = 1;
	}
	
	if (M_MovementInY!=0)
	{
		M_DirectionY = 1;
	}
}

void Enemy::Draw()
{
	std::cout << (char)153;
}

void Enemy::Update()
{
	if (M_MovementInX !=0)
	{
		UpdateDirection(M_CurrentMovementX, M_DirectionX, M_MovementInX);
	}
	if (M_MovementInY !=0)
	{
		UpdateDirection(M_CurrentMovementY, M_DirectionY, M_MovementInY);
	}
	this->SetPosition(M_pPosition->X, + M_DirectionX  + M_pPosition->Y + M_DirectionY);
	
}

void Enemy::UpdateDirection(int& Current, int& Direction, int& Movement)
{
	Current += Direction;
	if (std::abs(Current)>Movement)
	{
		Current = Movement * Direction;
		Direction *= -1;
	}
}
