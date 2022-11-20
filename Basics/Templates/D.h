//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef D_H
#define D_H

#include <string.h>

// REFACTOR this header to make it work
//     HINT: a few very small little changes are needed

// minimum of two values of any type (call-by-reference)
template <typename T>
const T &minD(T const& a, T const& b)
{
	if (a > b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

// minimum of two C-strings (call-by-pointer)
// the issue was this function was necer being called, even when char*s were passed into minD
// in all overloaded implementations we pass all arguments by reference, so we needed
// to add consts and references (const* const&) to all varables (return and parameters)
char const* const&minD(char const* const& a, char const* const& b)
{
	if (strcmp(a, b) > 0)
	{
		return b;
	}
	else
	{
		return a;
	}
}

// minimum of three values of any type (call-by-reference)
template <typename T>
const T &minD(T const &a, T const &b, T const &c)
{
	return minD(minD(a, b), c);
}


#endif

// ---  End of File ---------------
