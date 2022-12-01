//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef B_H
#define B_H

template <typename R, typename S, typename T>
T const minB(R const& a, S const& b)
{
	T val;

	if (a > b)
	{
		// need a cast incase type T != type S
		val = static_cast<T>(b);
	}
	else
	{
		// need a cast incase type T != type R
		val = static_cast<T>(a);
	}
	return  val;
}

int B();

#endif

// ---  End of File ---------------
