//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Matrix_Row_SIMD_H
#define Matrix_Row_SIMD_H

#include "Vect_Row_SIMD.h"
   
// -----------------------------------------------------------------------
// Rules: 
//    No implementation in Header
//    No inline keyword
// -----------------------------------------------------------------------

class Matrix_Row_SIMD
{
public:
	Matrix_Row_SIMD() = default;
	Matrix_Row_SIMD(const Matrix_Row_SIMD &tmp) = default;
	Matrix_Row_SIMD &operator=(const Matrix_Row_SIMD &tmp) = default;
	~Matrix_Row_SIMD() = default;

	Matrix_Row_SIMD(const Vect_Row_SIMD &tV0,
					const Vect_Row_SIMD &tV1,
					const Vect_Row_SIMD &tV2,
					const Vect_Row_SIMD &tV3);
 
	union
	{
		struct
		{
			Vect_Row_SIMD v0;
			Vect_Row_SIMD v1;
			Vect_Row_SIMD v2;
			Vect_Row_SIMD v3;
		};

		struct
		{
			float m0;
			float m1;
			float m2;
			float m3;
			float m4;
			float m5;
			float m6;
			float m7;
			float m8;
			float m9;
			float m10;
			float m11;
			float m12;
			float m13;
			float m14;
			float m15;
		};
	};
};

#endif

// ---  End of File ---------------
