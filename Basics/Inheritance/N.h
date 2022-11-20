//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef N_H
#define N_H

#include "M.h"

// ----------------------------------------------------------------------
//
// Problem 4
//
// Related files:  M.h, N.h, O.h, P.h
//
// Rules: 
//     Modify the classes to pass tests
//     The class should be in a diamond inheritance pattern
//     Only one variable in (M: a,b,c,d ) no duplicates or replicas
//
//     Modify P overload constructor to pass test
//     No body allowed in P's constructor
//
//     1) Do NOT modify class M in any way
//     2) Refactor class N to pass tests
//     3) Refactor class O to pass tests
//     4) Refactor class P to pass tests
//
// ----------------------------------------------------------------------

// -----------------------------------------------------
// REFACTOR class N,O,P - MODIFY this FILE
// -----------------------------------------------------

/*	need to add the virtual keyword, just like in class's G and F	*/
class N : virtual public M
{
public:
	N();

	N(int aVal, int bVal);

	void foo();

	int b;
};

#endif

// --- End of File ---
