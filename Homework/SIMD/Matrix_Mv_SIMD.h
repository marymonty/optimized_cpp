//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Matrix_Mv_SIMD_H
#define Matrix_Mv_SIMD_H

#include "Vect_Mv_SIMD.h"
   
// -----------------------------------------------------------------------
// Rules: 
//    No implementation in Header
//    No inline keyword
// -----------------------------------------------------------------------

class Matrix_Mv_SIMD
{
public:
	Matrix_Mv_SIMD() = default;
	Matrix_Mv_SIMD(const Matrix_Mv_SIMD &tmp) = default;
	Matrix_Mv_SIMD &operator=(const Matrix_Mv_SIMD &tmp) = default;
	~Matrix_Mv_SIMD() = default;

	Matrix_Mv_SIMD(const Vect_Mv_SIMD &tV0,
					const Vect_Mv_SIMD &tV1,
					const Vect_Mv_SIMD &tV2,
					const Vect_Mv_SIMD &tV3);

	Vect_Mv_SIMD operator * (const Vect_Mv_SIMD & v) const;
 
	union
	{
		struct
		{
			Vect_Mv_SIMD v0;
			Vect_Mv_SIMD v1;
			Vect_Mv_SIMD v2;
			Vect_Mv_SIMD v3;
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
