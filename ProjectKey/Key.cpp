#include "Key.h"
#include <iostream>
#include <Windows.h>


void Key::Draw()
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console, M_Color);

	std::cout << "+";
	SetConsoleTextAttribute(Console, KRegulerColor);
}