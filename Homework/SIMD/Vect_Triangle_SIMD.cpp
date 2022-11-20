//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_TRIANGLE_SIMD.h"



Vect_TRIANGLE_SIMD::Vect_TRIANGLE_SIMD(const float tx, const float ty, const float tz, const float tw)
	:x(tx),y(ty),z(tz),w(tw)
{

}

// Length = sqrt of (x*x)+(y*y)+(z*z)
float Vect_TRIANGLE_SIMD::Length() const
{
	Vect_TRIANGLE_SIMD A;

	// A._m = [ Ax | Ay | Az | Aw ]
	// A._m = [ Ax | Ay | Az | Aw ]
	// B._m = [ Ax*Ax | Ay*Ay | Az*Az | Aw*Aw ]

	A._m = _mm_mul_ps(this->_m, this->_m);

	// B._m = [ Ax*Ax | Ay*Ay | Az*Az | Aw*Aw ]
	// we need Ax*Ax + Ay*Ay + Az*Az + Aw*Aw
	// C._m = [ Ax*Ax + Ay*Ay | Az*Az + Aw*Aw | Ax*Ax + Ay*Ay | Az*Az + Aw*Aw ]

	A._m = _mm_hadd_ps(A._m, A._m);

	// D._m = [ Ax*Ax + Ay*Ay + Az*Az + Aw*Aw | same | same | same ]

	A._m = _mm_hadd_ps(A._m, A._m);

	// E._m = [ sqrt(Ax*Ax + Ay*Ay + Az*Az + Aw*Aw) | same | same | same ]

	A._m = _mm_sqrt_ss(A._m);

	return A.x;
}

// Cross Product:
//	C.x = AyBz - ByAz
//	C.y = AzBx - BzAx
//	C.z = AxBy - BxAy
// where B vect is the input vect R
Vect_TRIANGLE_SIMD Vect_TRIANGLE_SIMD::Cross(const Vect_TRIANGLE_SIMD &R) const
{
	Vect_TRIANGLE_SIMD A;
	Vect_TRIANGLE_SIMD B;
	Vect_TRIANGLE_SIMD C;

	// we are looking at the vectors like this:
	//		   __	__	   __ 	__
	//	C.x = |Ay| |Bz| - |By| |Az|
	//	C.y = |Az| |Bx| - |Bz| |Ax|
	//	C.z = |Ax| |By| - |Bx| |Ay|
	//	so if we have A._m = [ Ax | Ay | Az | Aw ]
	//  we need to "shuffle" the vect to be [ Ay | Az | Ax | Aw ]

	// _MM_SHUFFLE is a helper function where input is the new index position
	// IN REVERSE ORDER, so _MM_SHUFFLE(3,0,2,1) gives us index 1, 2, 0, 3 (Ay, Az, Ax, Aw)
	A._m = _mm_shuffle_ps(this->_m, this->_m, _MM_SHUFFLE(3, 0, 2, 1));
	B._m = _mm_shuffle_ps(R._m, R._m, _MM_SHUFFLE(3, 1, 0, 2));
	A._m = _mm_mul_ps(A._m, B._m);

	C._m = _mm_shuffle_ps(R._m, R._m, _MM_SHUFFLE(3, 0, 2, 1));
	B._m = _mm_shuffle_ps(this->_m, this->_m, _MM_SHUFFLE(3, 1, 0, 2));
	C._m = _mm_mul_ps(C._m, B._m);
	
	// AB - CD
	B._m = _mm_sub_ps(A._m, C._m);

 	return B;
}

// area = 0.5f * len(TxR)
float Vect_TRIANGLE_SIMD::Area(const Vect_TRIANGLE_SIMD &T, const Vect_TRIANGLE_SIMD &R) 
{
	// first copy and paste the Cross function
	Vect_TRIANGLE_SIMD A;
	Vect_TRIANGLE_SIMD B;
	Vect_TRIANGLE_SIMD C;
	A._m = _mm_shuffle_ps(T._m, T._m, _MM_SHUFFLE(3, 0, 2, 1));
	B._m = _mm_shuffle_ps(R._m, R._m, _MM_SHUFFLE(3, 1, 0, 2));
	A._m = _mm_mul_ps(A._m, B._m);
	C._m = _mm_shuffle_ps(R._m, R._m, _MM_SHUFFLE(3, 0, 2, 1));
	B._m = _mm_shuffle_ps(T._m, T._m, _MM_SHUFFLE(3, 1, 0, 2));
	C._m = _mm_mul_ps(C._m, B._m);
	// AB - CD
	B._m = _mm_sub_ps(A._m, C._m);
	// B is the Cross Product

	// next copy and paste the Length function
	A._m = _mm_mul_ps(B._m, B._m);
	A._m = _mm_hadd_ps(A._m, A._m);
	A._m = _mm_hadd_ps(A._m, A._m);
	A._m = _mm_sqrt_ss(A._m);
	// A.x holds the length

	return 0.5f * A.x;
}


// ---  End of File ---

