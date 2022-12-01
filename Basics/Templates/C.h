//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef C_H
#define C_H

#include "C_Interface.h"

template <typename T>
ReturnType const minC(T const& a, T const& b)
{
	AZUL_UNUSED_VAR(&a);
	AZUL_UNUSED_VAR(&b);
	return  TEMPLATE_2_ARG;
}

ReturnType const minC(int const& a, int const& b)
{
	AZUL_UNUSED_VAR(&a);
	AZUL_UNUSED_VAR(&b);
	return NON_TEMPLATE_INT_ARG;
}

template <typename T>
ReturnType const minC(T const& a, T const& b, T const& c)
{
	AZUL_UNUSED_VAR(&a);
	AZUL_UNUSED_VAR(&b);
	AZUL_UNUSED_VAR(&c);
	return  TEMPLATE_3_ARG;
}

#endif

// ---  End of File ---------------
