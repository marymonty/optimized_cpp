//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "P.h"

// Add code here if needed

P::P()
	: d(44)
{
}

/* FIX: the initializer list needs to match the data layout in P.h:
*		initializing aVal, then bVal, then cVal, then dVal
*/
P::P(int aVal, int bVal, int cVal, int dVal) : 
		M(aVal),
		N(aVal, bVal),
		O(aVal, cVal),
		d(dVal)
{
	// No body allowed
	// Only initialize with initializer list
	AZUL_REPLACE_ME_STUB(aVal);
	AZUL_REPLACE_ME_STUB(bVal);
	AZUL_REPLACE_ME_STUB(cVal);
	AZUL_REPLACE_ME_STUB(dVal);
}

void P::foo()
{
}

// --- End of File ---
