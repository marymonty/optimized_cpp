//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ZIP_CODE_H
#define ZIP_CODE_H

// ----------------------------------
// MODIFY this file
// Add methods to this file and predicates (hint)
// ----------------------------------

struct ZipCode
{
	ZipCode();
	ZipCode(const ZipCode &r);
	ZipCode(const char *inS, const int inZip);
	~ZipCode();
	ZipCode & operator = (const ZipCode &in);
	
	/* MY CODE */
	// need the operator < to compare for inserting in the set
	bool operator < (const ZipCode & z) const;

	// ZipCode_has_zip
	// a struct that is our own functor predicate
	// has private data zip2, which stores the zipcode we need to search for in C.cpp
	struct ZipCode_has_zip
	{
		ZipCode_has_zip(const int i);
		bool operator()(const ZipCode& z);

	private:
		int zip2;
	};
	
	/* END OF MY CODE */

	// You need to leave the data alone... you can add methods
	int  zip;
	char s[4];
};

#endif

// ---  End of File ---
