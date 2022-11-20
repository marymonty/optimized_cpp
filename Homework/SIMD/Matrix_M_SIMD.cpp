//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_M_SIMD.h"
#include "Matrix_M_SIMD.h"

Matrix_M_SIMD::Matrix_M_SIMD(const Vect_M_SIMD &tV0,
							 const Vect_M_SIMD &tV1,
							 const Vect_M_SIMD &tV2,
							 const Vect_M_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

//	4x4 Matrix Multiplication 
//
//	| A | B | C | D |		| Q | R | S | T |
//	| E | F | G | H |  *	| U | V | W | X |
//  | I | J | K | L |		| Y | Z | ! | @ | 
//  | M | N | O | P |		| # | $ | % | ^ |
//
//		| AQ + BU + CY + D# | AR + BV + CZ + D$ | AS + BW + C! + D% | AT + BX + C@ + D^ |
//	=	| EQ + FU + GY + H# | ER + FV + GZ + H$ | ES + FW + G! + H% | ET + FX + G@ + H^ |
//		| IQ + JU + KY + L# | IR + JV + KZ + L$ | IS + JW + K! + L% | IT + JX + K@ + L^ |
//		| MQ + NU + OY + P# | MR + NV + OZ + P$ | MS + NW + O! + P% | MT + NX + O@ + P^ |

Matrix_M_SIMD Matrix_M_SIMD::operator * (const Matrix_M_SIMD &mb) const
{
	Matrix_M_SIMD Mout;

	//	| v.x | v.y | v.z | v.w |		| ma0  | ma1  | ma2  | ma3  |
	//	| v.x | v.y | v.z | v.w |	*	| ma4  | ma5  | ma6  | ma7  |
	//	| v.x | v.y | v.z | v.w |		| ma8  | ma9  | ma10 | ma11 |
	//	| v.x | v.y | v.z | v.w |		| ma12 | ma13 | ma14 | ma15 |
	//	
	//		| v.x * ma0  | v.x * ma1  | v.x * ma2  | v.x * ma3  |
	//	=	| v.y * ma4  | v.y * ma5  | v.y * ma6  | v.y * ma7  |
	//		| v.z * ma8  | v.z * ma9  | v.z * ma10 | v.z * ma11 |
	//		| v.w * ma12 | v.w * ma13 | v.w * ma14 | v.w * ma15 |
	//	
	// for each vector in "this" matrix
	// so our "matrix" multiplication can now look like: 
	// [ v.x | v.x | v.x | v.x ] * [ ma0  | ma1  | ma2  | ma3 ]
	// so there doesnt need to be any transposing of matrices
	//
	Mout.v0._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(this->v0.x), mb.v0._m), _mm_mul_ps(_mm_set_ps1(this->v0.y), mb.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(this->v0.z), mb.v2._m), _mm_mul_ps(_mm_set_ps1(this->v0.w), mb.v3._m)));

	Mout.v1._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(this->v1.x), mb.v0._m), _mm_mul_ps(_mm_set_ps1(this->v1.y), mb.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(this->v1.z), mb.v2._m), _mm_mul_ps(_mm_set_ps1(this->v1.w), mb.v3._m)));

	Mout.v2._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(this->v2.x), mb.v0._m), _mm_mul_ps(_mm_set_ps1(this->v2.y), mb.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(this->v2.z), mb.v2._m), _mm_mul_ps(_mm_set_ps1(this->v2.w), mb.v3._m)));

	Mout.v3._m = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set_ps1(this->v3.x), mb.v0._m), _mm_mul_ps(_mm_set_ps1(this->v3.y), mb.v1._m)),
		_mm_add_ps(_mm_mul_ps(_mm_set_ps1(this->v3.z), mb.v2._m), _mm_mul_ps(_mm_set_ps1(this->v3.w), mb.v3._m)));


	return Mout;
}


// ---  End of File ---------------
