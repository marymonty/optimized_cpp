//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "J.h"

// ----------------------------------------------------------------------
//
// J - Project
//
// Rules: Fix the code to correctly print the predicted output
//        no memory leak
//
// ----------------------------------------------------------------------

Dog::Dog(int val)
{

	pVal = new int;
	*pVal = val;
}

Dog::Dog(const Dog& d)
{
	pVal = new int;
	*pVal = *d.pVal;
}

Dog::~Dog()
{
	delete pVal;
}

// Do not modify this method
int Dog::GetVal(Dog d)
{
	return *(d.pVal);
}

// End of File
