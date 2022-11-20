//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "A.h"

// ----------------------------------------------------------------------
//
// A - Project
//
// Rules: 
//      Correct the output, pass the test
//
// Note: 
//      Class has to be initialied using the initializer list only
//      No initialization in the body of the constructor
//      Cannot change the signature of the constructor
//      Cannot change the initializer list
//		Can only change A.h
//
// Hint:
//		Understand why its wrong
//		Look at the first several items in Effective C++ book
//
// ----------------------------------------------------------------------

A::A(int start)  
	: Second(start), First(Second + 1)
{
}

int A::getFirst()
{
	return this->First;
}

int A::getSecond()
{
	return this->Second;
}

// End of File