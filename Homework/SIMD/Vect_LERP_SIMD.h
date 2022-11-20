//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Vect_LERP_SIMD_H
#define Vect_LERP_SIMD_H

#include <xmmintrin.h>
#include <smmintrin.h>  

// -----------------------------------------------------------------------
// Rules: 
//    No implementation in Header
//    No inline keyword
// -----------------------------------------------------------------------

class Vect_LERP_SIMD
{
public:
	Vect_LERP_SIMD() = default;
	Vect_LERP_SIMD(const Vect_LERP_SIMD &tmp) = default;
	Vect_LERP_SIMD &operator = (const Vect_LERP_SIMD &tmp) = default;
	~Vect_LERP_SIMD() = default;

	Vect_LERP_SIMD(const float tx, const float ty, const float tz, const float tw);

	static Vect_LERP_SIMD Lerp(const Vect_LERP_SIMD &a, const Vect_LERP_SIMD &b, const float t);

public:

	// anonymous union
	union
	{
		__m128	_m;

		// anonymous struct
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
