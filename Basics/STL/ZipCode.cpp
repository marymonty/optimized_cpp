//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "ZipCode.h"

// ----------------------------------
// MODIFY this file
// ----------------------------------

// add code here if you want

// sort alphabetically by second char in ZipCode char* s
bool ZipCode::operator < (const ZipCode& z) const
{
	bool lessThan = false;
	if ((char)this->s[1] < (char)z.s[1])
	{
		lessThan = true;
	}
	// there is no documentation for how to deal with ties, so I'll just compare first letter
	else if ((char)this->s[1] == (char)z.s[1])
	{
		if ((char)this->s[0] < (char)z.s[0])
		{
			lessThan = true;
		}
	}
	return lessThan;
}


// need to make our own functor predicate to compare just ZipCodes
// set the functor's zip2 variable to be the zipcode we are searching for
ZipCode::ZipCode_has_zip::ZipCode_has_zip(const int i)
	: zip2(i)
{
};
// then compare if the find_if function using that zip2 zipcode compared against
// all values in zippy
bool ZipCode::ZipCode_has_zip::operator()(const ZipCode& z)
{
	bool zipEqual = false;
	if ((int)z.zip == zip2)
	{
		zipEqual = true;
	}
	return zipEqual;
}












bool isEqualZip(const ZipCode& z)
{
	bool zipEqual = false;
	if ((int)z.zip == 0xBB77)
	{
		zipEqual = true;
	}
	return zipEqual;
}

// ---  End of File ---
