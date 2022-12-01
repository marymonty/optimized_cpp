//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Wrapper.h"

// Add code here if needed

/* MY CODE */
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

/* END OF MY CODE */

// --- End of File ---
