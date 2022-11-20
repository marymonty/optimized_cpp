//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Vect_vM_SIMD_H
#define Vect_vM_SIMD_H

#include <xmmintrin.h>
#include <smmintrin.h>  

class Matrix_vM_SIMD;

// -----------------------------------------------------------------------
// Rules: 
//    No implementation in Header
//    No inline keyword
// -----------------------------------------------------------------------

class Vect_vM_SIMD
{
public:
	Vect_vM_SIMD() = default;
	Vect_vM_SIMD(const Vect_vM_SIMD &tmp) = default;
	Vect_vM_SIMD &operator = (const Vect_vM_SIMD &tmp) = default;
	~Vect_vM_SIMD() = default;

	Vect_vM_SIMD(const float tx, const float ty, const float tz, const float tw);

	Vect_vM_SIMD operator * (const Matrix_vM_SIMD &ma) const;

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
