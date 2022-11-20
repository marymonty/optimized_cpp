//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_vM_SIMD.h"
#include "Matrix_vM_SIMD.h"

Vect_vM_SIMD::Vect_vM_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

//------------------------------
// For No proxy:
//------------------------------
// vect * matrix
//	
//	[ A | B | C | D ] * | E | F | I | J |
//						| K | L | M | N |
//						| O | P | Q | R |
//						| S | T | U | V |
//
//	=	[ AE + BK + CO + DS | AF + BL + CP + DT | AI + BM + CQ + DU | AJ + BN + CR + DV ]
//
Vect_vM_SIMD Vect_vM_SIMD::operator * (const Matrix_vM_SIMD &ma) const
{
	//	| v.x | v.y | v.z | v.w |		| ma0  | ma1  | ma2  | ma3  |
	//								*	| ma4  | ma5  | ma6  | ma7  |
	//									| ma8  | ma9  | ma10 | ma11 |
	//									| ma12 | ma13 | ma14 | ma15 |
	//	
	//		| v.x * ma0  | v.x * ma1  | v.x * ma2  | v.x * ma3  |
	//	=	| v.y * ma4  | v.y * ma5  | v.y * ma6  | v.y * ma7  |
	//		| v.z * ma8  | v.z * ma9  | v.z * ma10 | v.z * ma11 |
	//		| v.w * ma12 | v.w * ma13 | v.w * ma14 | v.w * ma15 |
	//	
	// so our vM multiplication can now look like: 
	// [ v.x | v.x | v.x | v.x ] * [ ma0  | ma1  | ma2  | ma3 ]
	// for each "row*col" multiplication, or in our case const*row
	// so there doesnt need to be any transposing of matrices
	//
	Vect_vM_SIMD Vout;

	Vout._m = _mm_add_ps (_mm_add_ps(_mm_mul_ps(_mm_set_ps1(this->x), ma.v0._m), _mm_mul_ps(_mm_set_ps1(this->y), ma.v1._m)),
	_mm_add_ps(_mm_mul_ps(_mm_set_ps1(this->z), ma.v2._m), _mm_mul_ps(_mm_set_ps1(this->w), ma.v3._m)));
	
	return Vout;
};


// ---  End of File ---------------


