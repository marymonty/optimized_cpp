//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_Row_SIMD.h"
#include "Matrix_Row_SIMD.h"


Matrix_Row_SIMD::Matrix_Row_SIMD(const Vect_Row_SIMD &tV0,
								 const Vect_Row_SIMD &tV1,
								 const Vect_Row_SIMD &tV2,
								 const Vect_Row_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

// ---  End of File ---------------
