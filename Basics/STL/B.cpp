//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <list>
#include <algorithm>
#include <functional>
#include <vector>

#include "B.h"

int B[] = 
{
	66,
	77,
	33,
	22,
	88,
	11,
	99,
	44
};

int JunkDataB(555);

void Problem_B(	std::vector<int> &UnitTest_B_orig, 
				std::vector<int> &UnitTest_B_insert, 
				std::vector<int> &UnitTest_B_sort)
{
	// ----------------------------------------------------
	// a) Load the B[] data into a list
	//    Name the list: B_List
	// ----------------------------------------------------

	/* MY CODE */
	std::list<int> B_List;
	unsigned int B_size = sizeof(B) / sizeof(int);
	B_List.assign(B, B + B_size);
	
	/* END OF MY CODE */

		// ---------------------------------------------------------------------
		// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
		// ---------------------------------------------------------------------
		UnitTest_B_orig.assign(B_List.begin(), B_List.end());

	// ----------------------------------------------------
	// b) Insert the number '55' between 22 and 88 into B_List
	//    No brute force, assume there are 1000000 numbers before 22 and after 88.
	//    No iterative, simple approach, use the appropriate STL calls for efficiency
	// ----------------------------------------------------

		/* MY CODE */
		std::list<int>::iterator find22 = std::find(B_List.begin(), B_List.end(), 22);
		std::list<int>::iterator find88 = std::find(B_List.begin(), B_List.end(), 88);
		if (std::next(find22, 1) == find88)
		{
			B_List.insert(std::next(find22, 1), 55);
		}
		// else the 22 and 88 are not in sequence
		else if (find22 != B_List.end())
		{
			// we will go through finding all 2's and 8's to see if a pair exists in sequence
			while (find22 != B_List.end())
			{
				while (find88 != B_List.end())
				{
					if (std::next(find22, 1) == find88)
					{	// found a sequence, so make the insert
						B_List.insert(std::next(find22, 1), 55);
					}
					else
					{	// go to the next 8
						find88 = std::find(std::next(find88, 1), B_List.end(), 8);
					}
				}
				// no sequence found with that 2, go to the next and start over on 8s
				find22 = std::find(std::next(find22, 1), B_List.end(), 2);
				// we dont have to start at the beginning, just after the initial 2
				find88 = std::find(std::next(find22, 1), B_List.end(), 8);
			}
		}
	
	/* END OF MY CODE */


		// ---------------------------------------------------------------------
		// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
		// ---------------------------------------------------------------------
		UnitTest_B_insert.assign(B_List.begin(), B_List.end());

	// ----------------------------------------------------
	// c) sort the list in reverse order using the built in functional functions
	//        Largest to Smallest
	// ----------------------------------------------------

		/* MY CODE */
		B_List.sort();
		B_List.reverse();
	
	/* END OF MY CODE */

		// ---------------------------------------------------------------------
		// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
		// ---------------------------------------------------------------------
		UnitTest_B_sort.assign(B_List.begin(), B_List.end());
}

// ---  End of File ---
