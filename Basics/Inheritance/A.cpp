//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "A.h"

// Add code here if needed

A::A()
	: x(5)
{
}

/* FIX: VIRTUAL DESTRUCTOR
*		this A base class needs to have a virtual destructor
*		Virtual destructors are needed when an instance of the 
*		derived class (B) can be deleted through an A* (which is what Public1 tests)
*		Without virtual, when the destructor is called, the Base class destructor is
*		called, but not the derived class destructor, which is why we were leaking memory
*/
A::~A()
{

}

int A::getX()
{
	return this->x;
}

// --- End of File ---
