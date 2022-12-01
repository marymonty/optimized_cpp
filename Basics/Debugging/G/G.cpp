//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "G.h"

// ----------------------------------------------------------------------
//
// G - Project
//
// Rules: There is a subtle bug
//        If you break point and walk it, you wont see the bug
//        Leave as much as possible of the original function alone
//        The bug is very small and subtle
//
// ----------------------------------------------------------------------

// allocates an array of n integers
int *ArrayOfInt(int num)
{
	// FIX: needed to cast num to be an unsigned int to properly index
	return new int[(unsigned int)num];
}

// End of File
