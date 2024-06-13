#include "Player.h"
#include <iostream>
using namespace std; 
constexpr char PlayerSymbol = '@';
Player::Player():M_HasKey{false}
{
}

Player::~Player()
{
}

bool Player::HasKey()
{
	return M_HasKey;
}

void Player::SetPosition(int X, int Y)
{
	M_Position.X = X;
	M_Position.Y = Y;
}

void Player::PickUpKeyInLevel()
{
	M_HasKey = true;
}

void Player::UseKey()
{
	M_HasKey = true;
}

void Player::Draw()
{
	cout << PlayerSymbol << endl;
}
