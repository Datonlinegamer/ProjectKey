#include "Player.h"
#include <iostream>
#include "Key.h"
using namespace std; 
constexpr char PlayerSymbol = '@';
constexpr int KstartingLives = 3;
Player::Player() :
	PlaceableActor(0, 0), M_pCurrentKey{ nullptr }, M_Money{ 0 }, M_Lives{KstartingLives}
{
}


bool Player::HasKey()
{
	return M_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColor color)
{
	return HasKey() && M_pCurrentKey->GetColor() == color;
}




void Player::PickUpKeyInLevel(Key* Key)
{
	M_pCurrentKey = Key;
	
}

void Player::UseKey()
{
	M_pCurrentKey->Remove();
	M_pCurrentKey = nullptr;
}

void Player::DropKey()
{
	if (M_pCurrentKey)
	{
		M_pCurrentKey->Place(M_pPosition->X, M_pPosition->Y);
		M_pCurrentKey = nullptr;
	}
}

void Player::Draw()
{
	cout << PlayerSymbol << endl;
	
}
