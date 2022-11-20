//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_vM_SIMD.h"
#include "Matrix_vM_SIMD.h"


Matrix_vM_SIMD::Matrix_vM_SIMD(const Vect_vM_SIMD &tV0,
								 const Vect_vM_SIMD &tV1,
								 const Vect_vM_SIMD &tV2,
								 const Vect_vM_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

// ---  End of File ---------------
