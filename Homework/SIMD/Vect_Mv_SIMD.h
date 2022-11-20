//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Vect_Mv_SIMD_H
#define Vect_Mv_SIMD_H

#include <xmmintrin.h>
#include <smmintrin.h>  

class Matrix_Mv_SIMD;

// -----------------------------------------------------------------------
// Rules: 
//    No implementation in Header
//    No inline keyword
// -----------------------------------------------------------------------

class Vect_Mv_SIMD
{
public:
	Vect_Mv_SIMD() = default;
	Vect_Mv_SIMD(const Vect_Mv_SIMD &tmp) = default;
	Vect_Mv_SIMD &operator = (const Vect_Mv_SIMD &tmp) = default;
	~Vect_Mv_SIMD() = default;

	Vect_Mv_SIMD(const float tx, const float ty, const float tz, const float tw);

public:

	union
	{
		__m128	_m;

		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
};

#endif

// ---  End of File ---------------
