//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <vector>
#include <algorithm>

#include "D.h"
#include "Vect.h"

Vect V[] =
{
	{3,5,6},
	{6,5,3},
	{3,4,7},
	{7,2,5},
	{1,3,5},
	{3,2,5},
	{2,3,4},
	{3,5,5},
	{7,3,2},
	{4,3,2},
	{1,7,1}
};

Vect JunkDataD{ 0xa,0xb,0x3 };

void Problem_D(	std::vector< Vect > &UnitTest_V_orig,
				std::vector< Vect > &UnitTest_V_sort)
{	
	// ----------------------------------------------------
	// a) Load the V[] data into a vector
	//    Name the vector: v
	// ----------------------------------------------------

	/* MY CODE */
	std::vector<Vect> v(std::begin(V), std::end(V));
	
	/* END OF MY CODE */

		// ---------------------------------------------------------------------
		// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
		// ---------------------------------------------------------------------
		UnitTest_V_orig.assign(v.begin(), v.end());

	// ----------------------------------------------------
	// b) Sort the new STL vector with strict weak ordering
	//    Don't know what strict weak ordering is... Look it up
	// ----------------------------------------------------

		/* MY CODE */
		std::sort(v.begin(), v.end());
	
		/* END OF MY CODE */

		// ---------------------------------------------------------------------
		// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
		// ---------------------------------------------------------------------
		UnitTest_V_sort.assign(v.begin(), v.end());
}

// ---  End of File ---
