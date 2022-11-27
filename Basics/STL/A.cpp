//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <vector>
#include <algorithm>

#include "A.h"

int A[] = 
{
	6,
	7,
	3,
	2,
	8,
	1,
	9,
	4
};

int JunkDataA(777);

void Problem_A( std::vector<int> &UnitTest_A_orig, 
				std::vector<int> &UnitTest_A_insert, 
				std::vector<int> &UnitTest_A_sort)
{
	// ----------------------------------------------------
	// a) Load the A[] data into a vector
	//    Name the vector: A_Vector
	// ----------------------------------------------------

	/* MY CODE */
	// get the size of the int array first
	unsigned int A_size = sizeof(A) / sizeof(int);
	std::vector<int> A_Vector;
	A_Vector.insert(A_Vector.end(), &A[0], A+A_size);
	
	/* END MY CODE */

		// ---------------------------------------------------------------------
		// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
		// ---------------------------------------------------------------------
		UnitTest_A_orig.assign(A_Vector.begin(), A_Vector.end());

	// ----------------------------------------------------
	// b) Insert the number '5' between '2' and '8' values into A_Vector
	//    No brute force, assume there are 1000000 numbers before "2" and after "8".
	//    No iterative, simple approach, use the appropriate STL calls for efficiency
	// ----------------------------------------------------

		/* MY CODE */
		// prob uses std::find
		std::vector<int>::iterator found2 = std::find(A_Vector.begin(), A_Vector.end(), 2);
		std::vector<int>::iterator found8 = std::find(A_Vector.begin(), A_Vector.end(), 8);
		// not sure this is necessary, but I am making sure the 2 and 8 are in sequence
		if (found2 + 1 == found8)
		{
			A_Vector.insert(found2 + 1, 5);
		}
		// the 2 and 8 are not in sequence
		else if (found2 != A_Vector.end())
		{
			// we will go through finding all 2's and 8's to see if a pair exists in sequence
			while (found2 != A_Vector.end())
			{
				while (found8 != A_Vector.end())
				{
					if (found2 + 1 == found8)
					{	// found a sequence, so make the insert
						A_Vector.insert(found2 + 1, 5);
					}
					else
					{	// go to the next 8
						found8 = std::find(found8 + 1, A_Vector.end(), 8);
					}
				}
				// no sequence found with that 2, go to the next and start over on 8s
				found2 = std::find(found2 + 1, A_Vector.end(), 2);
				// we dont have to start at the beginning, just after the initial 2
				found8 = std::find(found2 + 1, A_Vector.end(), 8);
			}
		}
	
		/* END OF MY CODE */
		
		// ---------------------------------------------------------------------
		// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
		// ---------------------------------------------------------------------
		UnitTest_A_insert.assign(A_Vector.begin(), A_Vector.end());

	// ----------------------------------------------------
	// c) sort the A_Vector
	//          Smallest to largest order
	// ----------------------------------------------------

		/* MY CODE */
		std::sort(A_Vector.begin(), A_Vector.end());
	
		/* END OF MY CODE */

		// ---------------------------------------------------------------------
		// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
		// ---------------------------------------------------------------------
		UnitTest_A_sort.assign(A_Vector.begin(), A_Vector.end());

}

// ---  End of File ---
