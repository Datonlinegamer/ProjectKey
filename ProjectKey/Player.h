#pragma once
#include "PlaceableActor.h"
class Key;
class Player :public PlaceableActor
{
public:
	Player();
	


bool HasKey();
bool HasKey(ActorColor);
virtual ActorType GetType() override { return ActorType::Player; }

void AddMoney(int Money) { M_Money += Money; }
void PickUpKeyInLevel(Key* Key);
void UseKey();
void DropKey();
Key* GetKey() { return m_pCurrentKey; }
int GetMoney() { return M_Money; }

int GetLives() { return M_Lives; }
void DecrementLives() { --M_Lives; }

virtual void Draw()override;
private:
	Key* m_pCurrentKey;
	bool M_HasKey;
	int M_Money;
	int M_Lives;
};