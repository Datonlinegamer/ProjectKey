#include "Door.h"
#include "Windows.h"
#include <iostream>
Door::Door(int X, int Y, int Color, int CloseDoorColor)
	:PlaceableActor{ X,Y,Color }, M_IsOpen{false},M_CloseColor{CloseDoorColor}
{
}

void Door::Draw()
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (M_IsOpen)
	{
		SetConsoleTextAttribute(Console, M_Color);
	}
	else
	{
		SetConsoleTextAttribute(Console, M_CloseColor);

	}
	std::cout << "|";
	SetConsoleTextAttribute(Console, KRegulerColor);
}
