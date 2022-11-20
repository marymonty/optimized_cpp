//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "D.h"

// Add code here if needed

D::D()
	: z(55)
{
}

/*	
*		Need to specify that we are using the non-default C class constructor
*		in order to input the correct xVal and yVal
*/
D::D(int xVal, int yVal, int zVal) : C(xVal, yVal)
{
	// x and y are set through C's constructor call in the definition above
	// just need to set the z value
	this->z = zVal;
}

int D::getZ()
{
	return this->z;
}

// --- End of File ---
