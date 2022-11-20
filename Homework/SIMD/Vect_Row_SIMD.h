//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Vect_Row_SIMD_H
#define Vect_Row_SIMD_H

#include <xmmintrin.h>
#include <smmintrin.h>  

class Matrix_Row_SIMD;

// -----------------------------------------------------------------------
// Rules: 
//    Implement for Row Major
//    No implementation in Header
//
//    Proxy (optional)
//    
//        Proxies are the only thing that can have the keyword "inline"
//            inline only for subsitution resolving.. that's it
//                No constructors or other operators... only proxy for substituion purpose
//            example:  (this is allowed)
//                inline vM operator * (const Vect_Row_SIMD &v, const Matrix_Row_SIMD &m)
//        No proxy implementation in header
//            conversion operator needs to be implemented in CPP file
//            proxy constructors are allowed in header (only exception)
// -----------------------------------------------------------------------

class Vect_Row_SIMD
{
public:
	Vect_Row_SIMD() = default;
	Vect_Row_SIMD(const Vect_Row_SIMD &tmp) = default;
	Vect_Row_SIMD &operator = (const Vect_Row_SIMD &tmp) = default;
	~Vect_Row_SIMD() = default;

	Vect_Row_SIMD(const float tx, const float ty, const float tz, const float tw);

	// we use proxies instead of this
	//Vect_Row_SIMD operator * ( const Matrix_Row_SIMD &ma);


	// Proxy
	
	// vM
	//		Vect_Row_SIMD * Matrix_Row_SIMD
	//
	struct vM
	{
		const Vect_Row_SIMD& v;
		const Matrix_Row_SIMD& M;

		vM(const Vect_Row_SIMD& t1, const Matrix_Row_SIMD& t2)
			: v(t1), M(t2) {};

		//conversion operator implemented in cpp
		operator Vect_Row_SIMD();
	};
	friend inline vM operator * (const Vect_Row_SIMD& v, const Matrix_Row_SIMD& m)
	{
		return vM(v, m);
	};

	// vMM
	//		vM * Matrix_Row_SIMD
	//
	struct vMM
	{
		const Vect_Row_SIMD& v;
		const Matrix_Row_SIMD& M1;
		const Matrix_Row_SIMD& M2;

		vMM(const vM& t1, const Matrix_Row_SIMD& t2)
			: v(t1.v), M1(t1.M), M2(t2) {};

		//conversion operator implemented in cpp
		operator Vect_Row_SIMD();
	};
	friend inline vMM operator * (const vM& v, const Matrix_Row_SIMD& m)
	{
		return vMM(v, m);
	};


	// vMMM
	//		vMM * Matrix_Row_SIMD
	//
	struct vMMM
	{
		const Vect_Row_SIMD& v;
		const Matrix_Row_SIMD& M1;
		const Matrix_Row_SIMD& M2;
		const Matrix_Row_SIMD& M3;

		vMMM(const vMM& t1, const Matrix_Row_SIMD& t2)
			: v(t1.v), M1(t1.M1), M2(t1.M2), M3(t2) {};

		//conversion operator implemented in cpp
		operator Vect_Row_SIMD();
	};
	friend inline vMMM operator * (const vMM& v, const Matrix_Row_SIMD& m)
	{
		return vMMM(v, m);
	};


	// vMMMM
	//		vMMM * Matrix_Row_SIMD
	//
	struct vMMMM
	{
		const Vect_Row_SIMD& v;
		const Matrix_Row_SIMD& M1;
		const Matrix_Row_SIMD& M2;
		const Matrix_Row_SIMD& M3;
		const Matrix_Row_SIMD& M4;

		vMMMM(const vMMM& t1, const Matrix_Row_SIMD& t2)
			: v(t1.v), M1(t1.M1), M2(t1.M2), M3(t1.M3), M4(t2) {};

		//conversion operator implemented in cpp
		operator Vect_Row_SIMD();
	};
	friend inline vMMMM operator * (const vMMM& v, const Matrix_Row_SIMD& m)
	{
		return vMMMM(v, m);
	};


	// vMMMMM
	//		vMMMM * Matrix_Row_SIMD
	//
	struct vMMMMM
	{
		const Vect_Row_SIMD& v;
		const Matrix_Row_SIMD& M1;
		const Matrix_Row_SIMD& M2;
		const Matrix_Row_SIMD& M3;
		const Matrix_Row_SIMD& M4;
		const Matrix_Row_SIMD& M5;

		vMMMMM(const vMMMM& t1, const Matrix_Row_SIMD& t2)
			: v(t1.v), M1(t1.M1), M2(t1.M2), M3(t1.M3), M4(t1.M4), M5(t2) {};

		//conversion operator implemented in cpp
		operator Vect_Row_SIMD();
	};
	friend inline vMMMMM operator * (const vMMMM& v, const Matrix_Row_SIMD& m)
	{
		return vMMMMM(v, m);
	};



public:

	// anonymous union
	union
	{
		__m128	_m;

		// anonymous struct
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
};

#endif

// ---  End of File ---------------
