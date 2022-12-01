//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef WRAPPER_H
#define WRAPPER_H

#include "MiddlewareNative.h"

// ----------------------------------------------------------------------
//
// Problem 5
//
// Related files:  MiddlewareNative.h, Wrapper.h
//
// Rules: 
//     For this problem, you are wrapping a poor interface provided by a middleware vendors
//
//     This is a mockup of a middleware class
//         Too many functions and/or incorrect were provided to the End User
//
// The GameVect class needs to derive privately from Vect2D_Native
//
// Requirements:
//
//     1) variables:  x, y should be private
//     2) prevent methods setID() and getID() from being called from the wrapper class
//     3) prevent the original getX() and getY() from being called from the wrapper class
//     4) add to wrapper class: void getX(float &) return value as a float reference
//     5) add to wrapper class: void getY(float &) return value as a float reference
//     6) allow setX() and setY() to be called as-is from the wrapper class
//
// Run Basics2Debug.sln - should generate no errors and pass the tests
// Run Basics2Wrapper.sln to make sure your code is producing the correct errors
//
// Rules:
//
//     1) Do NOT modify class Vect2D_Native
//     2) GameVect class in Wrapper.h must derive privately from Vect2D_Native
//     3) Refactor GameVect class to meet the above requirements
//
// ----------------------------------------------------------------------

// -----------------------------------------------------
// REFACTOR class GameVect - MODIFY this FILE
// -----------------------------------------------------

/* The name of the game for this wrapper class is the keyword "using"
*		using allows us to hide functionality of the base class so it cannot be 
*		accessed through the derived class, which is exactly what we want.
*		We use all of Vect2D_Native functions, but the ones we shouldn't access
*		are now in the private methods of the GameVect class. The functions we 
*		call directly from the base class (setX and setY) are still being "used"
*		but they remain public. 
*/
class GameVect : private Vect2D_Native
{
public:
	/* MY CODE */
	// REMEMBER - you cannot reimplement setX() or setY()
	GameVect();
	virtual ~GameVect();
	// 4) add to wrapper class : void getX(float&) return value as a float reference
	void getX(float& storeX);
	// 5) add to wrapper class: void getY(float &) return value as a float reference
	void getY(float& storeY);
	// 6) allow setX() and setY() to be called as - is from the wrapper class
	using Vect2D_Native::setX;
	using Vect2D_Native::setY;
	/* END OF MY CODE */

private:
	// REMEMBER - you cannot add data
	
	/* MY CODE */
	// 1) variables:  x, y should be private
	using Vect2D_Native::x;
	using Vect2D_Native::y;
	// 2) prevent methods setID() and getID() from being called from the wrapper class
	using Vect2D_Native::setID;
	using Vect2D_Native::getID;
	// 3) prevent the original getX() and getY() from being called from the wrapper class
	using Vect2D_Native::getX;
	using Vect2D_Native::getY;
	/* END OF MY CODE */
};

#endif

// --- End of File ---
