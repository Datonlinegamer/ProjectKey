#pragma once
#include "PlaceableActor.h"
class Key;
class Player :public PlaceableActor
{
public:
	Player();
	


bool HasKey();
bool HasKey(ActorColor);


void AddMoney(int Money) { M_Money += Money; }
void PickUpKeyInLevel(Key* Key);
void UseKey();
void DropKey();

int GetMoney() { return M_Money; }

int GetLives() { return M_Lives; }
void DecrementLives() { M_Lives; }

virtual void Draw()override;
private:
	Key* M_pCurrentKey;
	bool M_HasKey;
	int M_Money;
	int M_Lives;
};