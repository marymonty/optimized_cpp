//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "H.h"

// ----------------------------------------------------------------------
//
// H - Project
//
// Rules: Expected to sum the numbers from 1 to 9, 
//        fixed the getNum() function
//        As ugly as this function is..., keep the same logic
//
// ----------------------------------------------------------------------

// Function getNum(), returns true/false, increments n
// we need n to be saving the value - so pass by reference
bool getNum(int &n)
{
	n = n + 1;

	if (n < 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// End of File