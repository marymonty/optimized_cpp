//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef D_H
#define D_H

#include "C.h"

// ----------------------------------------------------------------------
//
// Problem 2
//
// Related files:  C.h, D.h
//
// Rules: 
//     FIX class D to pass the unit tests
//
//     1) Do NOT modify class C in any way
//     2) Only modify Class D's constructor to pass the class
//
// ----------------------------------------------------------------------

// -----------------------------------------------------
// REFACTOR class D - MODIFY this FILE
//    Only the D's constructor
// -----------------------------------------------------

class D : public C
{
public:
	D();

	D(int xVal, int yVal, int zVal);

	int getZ();

private:
	int z;

};

#endif

// --- End of File ---
