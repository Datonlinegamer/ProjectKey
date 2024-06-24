#include "Goal.h"
#include <iostream>

Goal::Goal(int X, int Y):PlaceableActor(X,Y)
{
}

void Goal::Draw()
{
	std::cout << "X";
}
