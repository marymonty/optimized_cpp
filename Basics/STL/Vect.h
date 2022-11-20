//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef VECT_H
#define VECT_H

// ----------------------------------
//  MODIFY this file
//  Add methods if you want (hint)
// ----------------------------------
struct Vect
{
	// You need to leave the data alone... you can add methods
	int a;
	int b;
	int c;

	Vect() = default;
	Vect(const Vect &) = default;
	Vect & operator = (const Vect &) = default;
	~Vect() = default;

	// need to add a comparative operator to sort
	bool operator < (const Vect& v) const;

};

#endif

// ---  End of File ---
