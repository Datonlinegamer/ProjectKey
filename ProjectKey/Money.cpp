#include "Money.h"
#include <iostream>

Money::Money(int x, int y, int worth)
	: PlaceableActor(x, y), M_Worth(worth)
{
}
void Money::Draw()
{
	std::cout << "$";
}