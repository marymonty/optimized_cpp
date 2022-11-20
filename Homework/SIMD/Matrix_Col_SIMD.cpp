//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_Col_SIMD.h"
#include "Matrix_Col_SIMD.h"

Matrix_Col_SIMD::Matrix_Col_SIMD(const Vect_Col_SIMD &tV0,
								 const Vect_Col_SIMD &tV1,
								 const Vect_Col_SIMD &tV2,
								 const Vect_Col_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

/*	We are using proxies so we dont need these definitions
Vect_Col_SIMD Matrix_Col_SIMD::operator * (const Vect_Col_SIMD &vb)
Matrix_Col_SIMD Matrix_Col_SIMD::operator * (const Matrix_Col_SIMD &mb)
*/


// MM
//		Matrix_Col_SIMD * Matrix_Col_SIMD
//
Matrix_Col_SIMD::MM::operator Matrix_Col_SIMD()
{
	// this conversion is for matrix M * vector v converted into a Vect_Col_SIMD
	Matrix_Col_SIMD Mout;

	Mout.v0._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v0.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v0.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v0.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v0.w), M2.v3._m)));

	Mout.v1._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v1.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v1.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v1.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v1.w), M2.v3._m)));

	Mout.v2._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v2.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v2.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v2.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v2.w), M2.v3._m)));

	Mout.v3._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v3.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v3.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v3.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v3.w), M2.v3._m)));
	
	return Mout;
}

// MMM
//		MM * Matrix_Col_SIMD
//
Matrix_Col_SIMD::MMM::operator Matrix_Col_SIMD()
{
	// this conversion is for matrix M * matrix M * matrix M converted into a Matrix_Col_SIMD
	Matrix_Col_SIMD Mout1;
	Matrix_Col_SIMD Mout2;
	// mult first two matrices
	Mout1.v0._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v0.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v0.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v0.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v0.w), M2.v3._m)));

	Mout1.v1._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v1.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v1.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v1.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v1.w), M2.v3._m)));

	Mout1.v2._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v2.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v2.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v2.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v2.w), M2.v3._m)));

	Mout1.v3._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v3.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v3.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v3.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v3.w), M2.v3._m)));

	//multiply with third matrix
	Mout2.v0._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v0.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v0.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v0.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v0.w), M3.v3._m)));

	Mout2.v1._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v1.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v1.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v1.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v1.w), M3.v3._m)));

	Mout2.v2._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v2.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v2.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v2.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v2.w), M3.v3._m)));

	Mout2.v3._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v3.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v3.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v3.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v3.w), M3.v3._m)));

	return Mout2;
}

// MMMM
//		MMM * Matrix_Col_SIMD
//
Matrix_Col_SIMD::MMMM::operator Matrix_Col_SIMD()
{
	// this conversion is for matrix M * matrix M * matrix M converted into a Matrix_Col_SIMD
	Matrix_Col_SIMD Mout1;
	Matrix_Col_SIMD Mout2;
	// mult first two matrices
	Mout1.v0._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v0.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v0.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v0.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v0.w), M2.v3._m)));

	Mout1.v1._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v1.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v1.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v1.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v1.w), M2.v3._m)));

	Mout1.v2._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v2.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v2.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v2.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v2.w), M2.v3._m)));

	Mout1.v3._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v3.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v3.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v3.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v3.w), M2.v3._m)));

	//multiply with third matrix
	Mout2.v0._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v0.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v0.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v0.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v0.w), M3.v3._m)));

	Mout2.v1._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v1.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v1.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v1.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v1.w), M3.v3._m)));

	Mout2.v2._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v2.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v2.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v2.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v2.w), M3.v3._m)));

	Mout2.v3._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v3.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v3.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v3.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v3.w), M3.v3._m)));

	// multiply with fourth matrix
	Mout1.v0._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v0.x), M4.v0._m), _mm_mul_ps(_mm_set_ps1(Mout2.v0.y), M4.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v0.z), M4.v2._m), _mm_mul_ps(_mm_set_ps1(Mout2.v0.w), M4.v3._m)));

	Mout1.v1._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v1.x), M4.v0._m), _mm_mul_ps(_mm_set_ps1(Mout2.v1.y), M4.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v1.z), M4.v2._m), _mm_mul_ps(_mm_set_ps1(Mout2.v1.w), M4.v3._m)));

	Mout1.v2._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v2.x), M4.v0._m), _mm_mul_ps(_mm_set_ps1(Mout2.v2.y), M4.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v2.z), M4.v2._m), _mm_mul_ps(_mm_set_ps1(Mout2.v2.w), M4.v3._m)));

	Mout1.v3._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v3.x), M4.v0._m), _mm_mul_ps(_mm_set_ps1(Mout2.v3.y), M4.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v3.z), M4.v2._m), _mm_mul_ps(_mm_set_ps1(Mout2.v3.w), M4.v3._m)));

	return Mout1;
}

// MMMMM
//		MMMM * Matrix_Col_SIMD
//
Matrix_Col_SIMD::MMMMM::operator Matrix_Col_SIMD()
{
	Matrix_Col_SIMD Mout1;
	Matrix_Col_SIMD Mout2;
	// mult first two matrices
	Mout1.v0._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v0.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v0.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v0.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v0.w), M2.v3._m)));

	Mout1.v1._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v1.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v1.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v1.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v1.w), M2.v3._m)));

	Mout1.v2._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v2.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v2.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v2.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v2.w), M2.v3._m)));

	Mout1.v3._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v3.x), M2.v0._m), _mm_mul_ps(_mm_set_ps1(M1.v3.y), M2.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(M1.v3.z), M2.v2._m), _mm_mul_ps(_mm_set_ps1(M1.v3.w), M2.v3._m)));

	//multiply with third matrix
	Mout2.v0._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v0.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v0.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v0.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v0.w), M3.v3._m)));

	Mout2.v1._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v1.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v1.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v1.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v1.w), M3.v3._m)));

	Mout2.v2._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v2.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v2.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v2.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v2.w), M3.v3._m)));

	Mout2.v3._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v3.x), M3.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v3.y), M3.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v3.z), M3.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v3.w), M3.v3._m)));

	// multiply with fourth matrix
	Mout1.v0._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v0.x), M4.v0._m), _mm_mul_ps(_mm_set_ps1(Mout2.v0.y), M4.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v0.z), M4.v2._m), _mm_mul_ps(_mm_set_ps1(Mout2.v0.w), M4.v3._m)));

	Mout1.v1._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v1.x), M4.v0._m), _mm_mul_ps(_mm_set_ps1(Mout2.v1.y), M4.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v1.z), M4.v2._m), _mm_mul_ps(_mm_set_ps1(Mout2.v1.w), M4.v3._m)));

	Mout1.v2._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v2.x), M4.v0._m), _mm_mul_ps(_mm_set_ps1(Mout2.v2.y), M4.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v2.z), M4.v2._m), _mm_mul_ps(_mm_set_ps1(Mout2.v2.w), M4.v3._m)));

	Mout1.v3._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v3.x), M4.v0._m), _mm_mul_ps(_mm_set_ps1(Mout2.v3.y), M4.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout2.v3.z), M4.v2._m), _mm_mul_ps(_mm_set_ps1(Mout2.v3.w), M4.v3._m)));

	// multiply with fifth matrix
	Mout2.v0._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v0.x), M5.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v0.y), M5.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v0.z), M5.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v0.w), M5.v3._m)));

	Mout2.v1._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v1.x), M5.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v1.y), M5.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v1.z), M5.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v1.w), M5.v3._m)));

	Mout2.v2._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v2.x), M5.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v2.y), M5.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v2.z), M5.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v2.w), M5.v3._m)));

	Mout2.v3._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v3.x), M5.v0._m), _mm_mul_ps(_mm_set_ps1(Mout1.v3.y), M5.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(Mout1.v3.z), M5.v2._m), _mm_mul_ps(_mm_set_ps1(Mout1.v3.w), M5.v3._m)));

	return Mout2;
}


// MMMMMv
//		MMMMM * Vect_Col_SIMD
//
Matrix_Col_SIMD::MMMMMv::operator Vect_Col_SIMD()
{
	Vect_Col_SIMD Vout;

	// mult last matrix (M5) * vect
	Vout._m = _mm_hadd_ps(_mm_hadd_ps(_mm_mul_ps(M5.v0._m, v._m), _mm_mul_ps(M5.v1._m, v._m)),
		_mm_hadd_ps(_mm_mul_ps(M5.v2._m, v._m), _mm_mul_ps(M5.v3._m, v._m)));

	//multiply second to last matrix (M4) with Vout
	Vout._m = _mm_hadd_ps(_mm_hadd_ps(_mm_mul_ps(M4.v0._m, Vout._m), _mm_mul_ps(M4.v1._m, Vout._m)),
		_mm_hadd_ps(_mm_mul_ps(M4.v2._m, Vout._m), _mm_mul_ps(M4.v3._m, Vout._m)));

	// multiply third to last matrix (M3) with Vout
	Vout._m = _mm_hadd_ps(_mm_hadd_ps(_mm_mul_ps(M3.v0._m, Vout._m), _mm_mul_ps(M3.v1._m, Vout._m)),
		_mm_hadd_ps(_mm_mul_ps(M3.v2._m, Vout._m), _mm_mul_ps(M3.v3._m, Vout._m)));

	// multiply fourth to last matrix (M2) with Vout
	Vout._m = _mm_hadd_ps(_mm_hadd_ps(_mm_mul_ps(M2.v0._m, Vout._m), _mm_mul_ps(M2.v1._m, Vout._m)),
		_mm_hadd_ps(_mm_mul_ps(M2.v2._m, Vout._m), _mm_mul_ps(M2.v3._m, Vout._m)));

	// multiply fifth to last matrix (M1) with Vout
	Vout._m = _mm_hadd_ps(_mm_hadd_ps(_mm_mul_ps(M1.v0._m, Vout._m), _mm_mul_ps(M1.v1._m, Vout._m)),
		_mm_hadd_ps(_mm_mul_ps(M1.v2._m, Vout._m), _mm_mul_ps(M1.v3._m, Vout._m)));

	return Vout;
}


// ---  End of File ---------------
