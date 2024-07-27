#include "Player.h"
#include <iostream>
#include "Key.h"
#include "AudioManager.h"
using namespace std; 
constexpr char PlayerSymbol = '@';
constexpr int KstartingLives = 3;
Player::Player() :
	PlaceableActor(0, 0), m_pCurrentKey
	( nullptr) ,
	M_Money( 0 )
	, M_Lives(KstartingLives)
{
}


bool Player::HasKey()
{
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColor color)
{
	return HasKey() && m_pCurrentKey->GetColor() == color;
}




void Player::PickUpKeyInLevel(Key* Key)
{
	m_pCurrentKey = Key;
	
}

void Player::UseKey()
{
	m_pCurrentKey->Remove();
	m_pCurrentKey = nullptr;
}

void Player::DropKey()
{
	if (m_pCurrentKey)
	{
		AudioManager::GetInstance()->PlayDropKeySound();
		m_pCurrentKey->Place(M_pPosition->X, M_pPosition->Y);
		m_pCurrentKey = nullptr;
	}
}

void Player::Draw()
{
	cout << PlayerSymbol << endl;
	
}
