#include "Key.h"
#include <iostream>
#include <Windows.h>


void Key::Draw()
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console, (int) M_Color);

	std::cout << "+";
	SetConsoleTextAttribute(Console,(int) ActorColor::KRegulerColor);
}