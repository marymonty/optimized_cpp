//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef A_H
#define A_H

template <typename T>
inline T const minA(T const& a, T const& b)
{

	T val;

	if (a > b)
	{
		val = b;
	}
	else
	{
		val = a;
	}

	return  val;
}

double A();


#endif

// ---  End of File ---------------
