//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// Add headers as you see fit
#include <algorithm>
#include <set>
#include <vector>

#include "C.h"
#include "ZipCode.h"

ZipCode data[] =
{
	ZipCode("Bug", 0xABCD),
	ZipCode("Dog", 0x1331),
	ZipCode("Cat", 0x8844),
	ZipCode("Pig", 0xBB77),
	ZipCode("Bee", 0xFFEE),
	ZipCode("Nbt", 0xCC99)
};

ZipCode JunkDataC{ "tmp", 0x0 };
/*
bool isEqual(const int& i)
{
	bool isTrue = false;
	if (this->zip == i)
	{
		isTrue = true;
	}
	return isTrue;
}*/

void Problem_C(	std::vector< ZipCode > &UnitTest_ZipSort,
				ZipCode &UnitTest_Bee,
				ZipCode &UnitTest_Zip)
{

	// ----------------------------------------------------
	// a) Insert the data into a stl:set in the order given.
	//    Use a compare function that sorts with the 2nd letter of the string 
	//          Smallest to largest
	//    Name the set: zippy
	// ----------------------------------------------------

		// ADD CODE HERE:
		std::set<ZipCode> zippy(std::begin(data), std::end(data));

		// ---------------------------------------------------------------------
		// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
		// ---------------------------------------------------------------------
		UnitTest_ZipSort.assign(zippy.begin(), zippy.end());
		
	// ----------------------------------------------------
	// b)  Find node {"Bee", 0xFFEE} in the set
	//     use the complete node in the search
	//     Initialize the iterator where it found the node
	//
	//     Name the set iterator: zippy_it
	// ----------------------------------------------------

		// ADD CODE HERE:
		std::set< ZipCode >::iterator zippy_it = zippy.find(ZipCode("Bee", 0xFFEE));


		// ---------------------------------------------------------------------
		// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
		// ---------------------------------------------------------------------
		UnitTest_Bee = *zippy_it;

	// ----------------------------------------------------
	// c)  Find the the string name associated with this zip data '0xBB77'
	//     Do not use the complete node, only the zip data
	//     Look at the node contents and iterator address
	//
	//     NOTE: you can only use STL: set  - no maps!
	//     hint:  use a custom predicate
	//
	//     Name the set iterator: zippy_it
	// ----------------------------------------------------

		// ADD CODE HERE:
		zippy_it = std::find_if(zippy.begin(), zippy.end(), ZipCode::ZipCode_has_zip(0xBB77));
		// ---------------------------------------------------------------------
		// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
		// ---------------------------------------------------------------------
		UnitTest_Zip = *zippy_it;

}

// ---  End of File ---
