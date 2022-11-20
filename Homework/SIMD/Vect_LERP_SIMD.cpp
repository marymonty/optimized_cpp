//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_LERP_SIMD.h"

Vect_LERP_SIMD::Vect_LERP_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

/*****************************************************************************
* LERP - linear interpolation
*
* This function returns a point on a line segment given in parametric form.
* Where the inputs are point a (starting point), point b (ending point) of
* the line segment and the parametric variable t.  If t is in the range of
* ranging from t=0.0 to 1.0, this function returns a point on the line
* segment. If t=0.0 this function returns point a, if t=1.0 this returns
* point b.  Values of t<0.0 return points on the infinite line defined
* before point a. Values of t>1.0 returns points on the infinite line
* defined after point b.
*
* inputs:
*		a - point A
*		b - point B
*		t - parametric t
*
* @return Vector (point) linearly interpolated based on parametric t
*
* Example:
*
*     Vect   v1(1.0f, 2.0f, 3.0f);   // create v1=[1,2,3,1]
*     Vect   v2(-5.0f, 2.0f, 7.0f);  // create v2=[-5,2,7,1]
*     Vect   out;                    // create out vector
*
*     out =	lineParametric (v1, v2, 0.4f );  // t = 0.4f

******************************************************************************/

Vect_LERP_SIMD Vect_LERP_SIMD::Lerp(const Vect_LERP_SIMD &a, const Vect_LERP_SIMD &b, const float t)
{
	Vect_LERP_SIMD C;
	Vect_LERP_SIMD D;
	Vect_LERP_SIMD E;
	Vect_LERP_SIMD F;
	
	//return  a + (b - a) * t;
	// a = [ ax | ay | az | aw ]
	// b = [ bx | by | bz | bw ]
	// c = [ bx-ax | by-ay | bz-az | bw-aw ]

	// c = b-a
	C._m = _mm_sub_ps(b._m, a._m);

	// D = [ t        | t        | t        | t        ]
	// C = [ bx-ax    | by-ay    | bz-az    | bw-aw    ]
	// E = [ t(bx-ax) | t(by-ay) | t(bz-az) | t(bw-aw) ]

	D._m = _mm_set1_ps(t);
	E._m = _mm_mul_ps(D._m, C._m);

	// a = [ ax          | ay          | az          | aw          ]
	// E = [ t(bx-ax)    | t(by-ay)    | t(bz-az)    | t(bw-aw)    ]
	// F = [ ax+t(bx-ax) | ay+t(by-ay) | az+t(bz-az) | aw+t(bw-aw) ]

	F._m = _mm_add_ps(E._m, a._m);

	return F;
}




// ---  End of File ---------------


