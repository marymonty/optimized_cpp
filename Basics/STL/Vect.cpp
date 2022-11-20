//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Vect.h"

// ----------------------------------
// MODIFY this file
// ----------------------------------

// ADD CODE HERE if needed:
// operator < needed for sorting the new vector in strict weak ordering
// which is just lowest numbers first, so 
// { 1, 3, 5 } would come before { 2, 1, 1 } because first position 1 < 2
// { 1, 3, 5 } would come before { 1, 6, 2 } because w/ first pos equal, second pos has  3 < 6
// { 1, 3, 5 } would come before { 1, 3, 8 } because first and second pos are equal, third pos has 5 < 8
bool Vect::operator < (const Vect& v) const
{
	bool lessThan = false;
	if (this->a < v.a)
	{	// first position (a) is smaller, so lessThan is true
		lessThan = true;
	}
	// else, a is either bigger or equal to v.a
	else if (this->a == v.a)
	{	// the a's are equal
		if (this->b < v.b)
		{	// second position (b) is smaller, so lessThan is true
			lessThan = true;
		}
		// else, b is either bigger or equal to v.b
		else if (this->b == v.b)
		{	// the a's and b's are equal
			if (this->c < v.c)
			{	// third position (c) is smaller, so lessThan is true
				lessThan = true;
			}
		}
	}
	return lessThan;
}

// ---  End of File ---
