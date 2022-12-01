//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef A_H
#define A_H
// ----------------------------------------------------------------------
//
// Problem 1
//
// Related files:  A.h, B.h
//
// Rules: 
//     FIX class A to prevent the memory leak in the unit tests
//
//     1) Only modify class A
//     2) Do NOT modify class B in any way
//
// ----------------------------------------------------------------------

// -----------------------------------------------------
// REFACTOR class A - MODIFY this FILE
// -----------------------------------------------------


// B derives from A

class A
{
public:
	A();

	//A& operator = (const A& a);
	
	// FIX: need to make the destructor virtual
	virtual ~A();

	int getX();
	int getConstX() const;

private:
	int x;
};

#endif

// --- End of File ---
