#pragma once
#include "Point.h"
class Player
{
public:
	Player();
	~Player();

int GetXPosition() {return M_Position.X;}
int GetYPosition() { return M_Position.Y; }

bool HasKey();

void SetPosition(int X ,int Y);
void PickUpKeyInLevel();
void UseKey();
void Draw();

int* GetXPositionPointer() {return	&(M_Position.X); }
int* GetYPositionPointer() {return	&(M_Position.Y); }

private:
	Point M_Position;
	bool M_HasKey;
};