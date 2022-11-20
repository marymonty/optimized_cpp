//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_Row_SIMD.h"
#include "Matrix_Row_SIMD.h"

Vect_Row_SIMD::Vect_Row_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

/*
* We use proxies instead of this function
Vect_Row_SIMD Vect_Row_SIMD::operator * ( const Matrix_Row_SIMD &ma)
*/


// vM
//		Vect_Row_SIMD * Matrix_Row_SIMD
//
Vect_Row_SIMD::vM::operator Vect_Row_SIMD()
{
	// this conversion is for vector V * matrix M converted into a Vect_Row_SIMD
	Vect_Row_SIMD Vout;

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(v.x), M.v0._m), _mm_mul_ps(_mm_set_ps1(v.y), M.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(v.z), M.v2._m), _mm_mul_ps(_mm_set_ps1(v.w), M.v3._m)));

	return Vout;
}

// vMM
//		vM * Matrix_Row_SIMD
//
Vect_Row_SIMD::vMM::operator Vect_Row_SIMD()
{
	// this conversion is for vector*matrix vM * matrix M converted into a Vect_Row_SIMD
	Vect_Row_SIMD Vout;

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(v.x), M1.v0._m), _mm_mul_ps(_mm_set_ps1(v.y), M1.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(v.z), M1.v2._m), _mm_mul_ps(_mm_set_ps1(v.w), M1.v3._m)));

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(Vout.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(Vout.w), M2.v3._m)));

	return Vout;
}

// vMMM
//		vMM * Matrix_Row_SIMD
//
Vect_Row_SIMD::vMMM::operator Vect_Row_SIMD()
{
	// this conversion is for vector*matrix*matrix vMM * matrix M converted into a Vect_Row_SIMD
	Vect_Row_SIMD Vout;

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(v.x), M1.v0._m), _mm_mul_ps(_mm_set_ps1(v.y), M1.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(v.z), M1.v2._m), _mm_mul_ps(_mm_set_ps1(v.w), M1.v3._m)));

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(Vout.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(Vout.w), M2.v3._m)));

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Vout.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Vout.w), M3.v3._m)));

	return Vout;
}

// vMMMM
//		vMMM * Matrix_Row_SIMD
//
Vect_Row_SIMD::vMMMM::operator Vect_Row_SIMD()
{
	// this conversion is for vector*matrix*matrix*matrix vM * matrix M 
	//	converted into a Vect_Row_SIMD
	Vect_Row_SIMD Vout;

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(v.x), M1.v0._m), _mm_mul_ps(_mm_set_ps1(v.y), M1.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(v.z), M1.v2._m), _mm_mul_ps(_mm_set_ps1(v.w), M1.v3._m)));

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(Vout.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(Vout.w), M2.v3._m)));

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Vout.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Vout.w), M3.v3._m)));

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.x), M4.v0._m), _mm_mul_ps(_mm_set_ps1(Vout.y), M4.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.z), M4.v2._m), _mm_mul_ps(_mm_set_ps1(Vout.w), M4.v3._m)));

	return Vout;
}

// vMMMMM
//		vMMMM * Matrix_Row_SIMD
//
Vect_Row_SIMD::vMMMMM::operator Vect_Row_SIMD()
{
	// this conversion is for vector*matrix*matrix*matrix*matrix vM * matrix M 
	//	converted into a Vect_Row_SIMD
	Vect_Row_SIMD Vout;

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(v.x), M1.v0._m), _mm_mul_ps(_mm_set_ps1(v.y), M1.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(v.z), M1.v2._m), _mm_mul_ps(_mm_set_ps1(v.w), M1.v3._m)));

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(Vout.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(Vout.w), M2.v3._m)));

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Vout.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Vout.w), M3.v3._m)));

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.x), M4.v0._m), _mm_mul_ps(_mm_set_ps1(Vout.y), M4.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.z), M4.v2._m), _mm_mul_ps(_mm_set_ps1(Vout.w), M4.v3._m)));

	Vout._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.x), M5.v0._m), _mm_mul_ps(_mm_set_ps1(Vout.y), M5.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Vout.z), M5.v2._m), _mm_mul_ps(_mm_set_ps1(Vout.w), M5.v3._m)));

	return Vout;
}

// ---  End of File ---------------


