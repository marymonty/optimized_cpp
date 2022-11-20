//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Matrix_Col_SIMD_H
#define Matrix_Col_SIMD_H

#include "Vect_Col_SIMD.h"
   
// -----------------------------------------------------------------------
// Rules: 
//    Implement for Col Major
//    No implementation in Header
//
//    Proxy (optional)
//    
//        Proxies are the only thing that can have the keyword "inline"
//            inline only for subsitution resolving.. that's it
//                No constructors or other operators... only proxy for substituion purpose
//            example:  (this is allowed)
//                inline MM operator * (const Matrix_Col_SIMD &m, const Matrix_Col_SIMD &n)
//        No proxy implementation in header
//            conversion operator needs to be implemented in CPP file
//            proxy constructors are allowed in header (only exception)
// -----------------------------------------------------------------------

class Matrix_Col_SIMD
{
public:
	Matrix_Col_SIMD() = default;
	Matrix_Col_SIMD(const Matrix_Col_SIMD &tmp) = default;
	Matrix_Col_SIMD &operator=(const Matrix_Col_SIMD &tmp) = default;
	~Matrix_Col_SIMD() = default;

	Matrix_Col_SIMD(const Vect_Col_SIMD &tV0,
					const Vect_Col_SIMD &tV1,
					const Vect_Col_SIMD &tV2,
					const Vect_Col_SIMD &tV3);
 
	// we are using proxies so we dont need these defined here
	//Matrix_Col_SIMD operator * (const Matrix_Col_SIMD &n);
	//Vect_Col_SIMD operator * (const Vect_Col_SIMD &n);

	// Proxy

	// MM
	//		Matrix_Col_SIMD * Matrix_Col_SIMD
	//
	struct MM
	{
		const Matrix_Col_SIMD& M1;
		const Matrix_Col_SIMD& M2;

		MM(const Matrix_Col_SIMD& t1, const Matrix_Col_SIMD& t2)
			: M1(t1), M2(t2) {};

		//conversion operator implemented in cpp
		operator Matrix_Col_SIMD();
	};
	friend inline MM operator * (const Matrix_Col_SIMD& m1, const Matrix_Col_SIMD& m2)
	{
		return MM(m1, m2);
	};

	// MMM
	//		MM * Matrix_Col_SIMD
	//
	struct MMM
	{
		const Matrix_Col_SIMD& M1;
		const Matrix_Col_SIMD& M2;
		const Matrix_Col_SIMD& M3;

		MMM(const MM& t1, const Matrix_Col_SIMD& t2)
			: M1(t1.M1), M2(t1.M2), M3(t2) {};

		//conversion operator implemented in cpp
		operator Matrix_Col_SIMD();
	};
	friend inline MMM operator * (const MM& m1, const Matrix_Col_SIMD& m2)
	{
		return MMM(m1, m2);
	};

	// MMMM
	//		MMM * Matrix_Col_SIMD
	//
	struct MMMM
	{
		const Matrix_Col_SIMD& M1;
		const Matrix_Col_SIMD& M2;
		const Matrix_Col_SIMD& M3;
		const Matrix_Col_SIMD& M4;

		MMMM(const MMM& t1, const Matrix_Col_SIMD& t2)
			: M1(t1.M1), M2(t1.M2), M3(t1.M3), M4(t2) {};

		//conversion operator implemented in cpp
		operator Matrix_Col_SIMD();
	};
	friend inline MMMM operator * (const MMM& m1, const Matrix_Col_SIMD& m2)
	{
		return MMMM(m1, m2);
	};

	// MMMMM
	//		MMMM * Matrix_Col_SIMD
	//
	struct MMMMM
	{
		const Matrix_Col_SIMD& M1;
		const Matrix_Col_SIMD& M2;
		const Matrix_Col_SIMD& M3;
		const Matrix_Col_SIMD& M4;
		const Matrix_Col_SIMD& M5;

		MMMMM(const MMMM& t1, const Matrix_Col_SIMD& t2)
			: M1(t1.M1), M2(t1.M2), M3(t1.M3), M4(t1.M4), M5(t2) {};

		//conversion operator implemented in cpp
		operator Matrix_Col_SIMD();
	};
	friend inline MMMMM operator * (const MMMM& m1, const Matrix_Col_SIMD& m2)
	{
		return MMMMM(m1, m2);
	};

	// MMMMMv
	//		MMMMM * Vect_Col_SIMD
	//
	struct MMMMMv
	{
		const Matrix_Col_SIMD& M1;
		const Matrix_Col_SIMD& M2;
		const Matrix_Col_SIMD& M3;
		const Matrix_Col_SIMD& M4;
		const Matrix_Col_SIMD& M5;
		const Vect_Col_SIMD& v;

		MMMMMv(const MMMMM& t1, const Vect_Col_SIMD& t2)
			: M1(t1.M1), M2(t1.M2), M3(t1.M3), M4(t1.M4), M5(t1.M5), v(t2) {};

		//conversion operator implemented in cpp
		operator Vect_Col_SIMD();
	};
	friend inline MMMMMv operator * (const MMMMM& m1, const Vect_Col_SIMD& m2)
	{
		return MMMMMv(m1, m2);
	};


	union
	{
		struct
		{
			Vect_Col_SIMD v0;
			Vect_Col_SIMD v1;
			Vect_Col_SIMD v2;
			Vect_Col_SIMD v3;
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
