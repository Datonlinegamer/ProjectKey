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
		if (MyGame.DidUserQuit())
		{
			cout << "Thank You For Playing!!!" << endl;
		}
		else if(MyGame.GetPlayerlives()<0)
		{
			cout << "YOU LOSE!!!" << endl;
		}
		else
		{
			cout << "YOU WON!!!" << endl;

		}
	}
	else
	{
		cout << "Game did not load. Teminating now!" << endl;
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
