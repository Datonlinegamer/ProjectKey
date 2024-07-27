#include"PlaceableActor.h"

PlaceableActor::PlaceableActor(int X, int Y, ActorColor Color) :
	M_pPosition{ new Point(X,Y) }, M_isActive(true), M_Color(Color)
{
}

PlaceableActor::~PlaceableActor()
{
	delete M_pPosition;
	M_pPosition = nullptr;
}

int PlaceableActor::GetXPosition()
{
	return M_pPosition->X;
	

}

int PlaceableActor::GetYPosition()
{
	return M_pPosition->Y;
	
}

int* PlaceableActor::GetXPositionPointer()
{
	return &(M_pPosition->X);
}

int* PlaceableActor::GetYPositionPointer()
{
	return &(M_pPosition->Y);
}

void PlaceableActor::SetPosition(int X, int Y)
{
	M_pPosition->X = X;
	M_pPosition->Y = Y;
}

void PlaceableActor::Place(int X, int Y)
{
	
	M_pPosition->X = X;
	M_pPosition->Y = Y;
	M_isActive = true;
}


