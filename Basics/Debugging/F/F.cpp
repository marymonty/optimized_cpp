//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "F.h"

// ----------------------------------------------------------------------
//
// F - Project
//
// Rules: fix the smal bug in the function, called findBitsInNibble
//        to output the correct number of '1' bits of any given number
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// Function: returns the number of 1 bits in a the data
// ----------------------------------------------------------------------
int FindBitsInNibble(unsigned int data)
{
	int n(0);
	// FIX:
	// two numbers were missing in the bitPattern (figured out below)
	// the bitPattern signifies the number of 1's in the binary representation
	// 1 = 0000 0001 (= 1 num bit)
	// 4 = 0000 0100 (= 1 num bit)
	// 7 = 0000 0111 = 3 num bits <- needs to be corrected
	// 14 is the other correction - it was missing - needed a 3 at index 14
	int bitPattern[NUM_BITS] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };

	while (data > 0)
	{
		n += bitPattern[data & 0xF];
		data >>= 4;
	}
	return n;
}

// End of File
