//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Wrapper.h"

// Add code here if needed
GameVect::GameVect()
{

}
GameVect::~GameVect()
{

}

// 4) add to wrapper class : void getX(float&) return value as a float reference
void GameVect::getX(float& storeX)
{
	storeX = x;
}
// 5) add to wrapper class: void getY(float &) return value as a float reference
void GameVect::getY(float& storeY)
{
	storeY = y;
}

// --- End of File ---