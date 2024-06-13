#include <iostream>

#include "Game.h"

using namespace std;


int main()
{
	Game MyGame;
	if (MyGame.Load())
	{
		while (!MyGame.IsGameOver())
		{
			MyGame.Run();
		}
		cout << "You won!!" << endl;
	}
	else
	{
		cout << "Something went wrong" << endl;
	}
}

//void playclosedoorsound()
//{
//    beep(500, 75);
//    beep(500, 75);
//}
//
//void playopensound()
//{
//    beep(1397, 200);
//}
//
//void playkeysound()
//{
//    beep(1568, 200);
//}
//
//void playwinsound()
//{
//    beep(1568, 200);
//    beep(1568, 200);
//    beep(1568, 200);
//    beep(1245, 1000);
//    beep(1397, 200);
//    beep(1397, 200);
//    beep(1397, 200);
//    beep(1175, 1000);
//    
//}
