//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Vect_Triangle_SIMD_H
#define Vect_Triangle_SIMD_H

#include <xmmintrin.h>
#include <smmintrin.h>  

// -----------------------------------------------------------------------
// Rules: 
//    No implementation in Header
//    No inline keyword
// -----------------------------------------------------------------------

class Vect_TRIANGLE_SIMD
{
public:
	Vect_TRIANGLE_SIMD() {};
	Vect_TRIANGLE_SIMD(const Vect_TRIANGLE_SIMD &tmp) = default;
	Vect_TRIANGLE_SIMD &operator = (const Vect_TRIANGLE_SIMD &tmp) = default;
	~Vect_TRIANGLE_SIMD() = default;

	Vect_TRIANGLE_SIMD(const float tx, const float ty, const float tz, const float tw);
	float Length() const;
	Vect_TRIANGLE_SIMD Cross(const Vect_TRIANGLE_SIMD &B) const;
	static float Area(const Vect_TRIANGLE_SIMD &A, const Vect_TRIANGLE_SIMD &B);


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
