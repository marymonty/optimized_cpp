//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef HOTDOG_H
#define HOTDOG_H

// Add files include as needed
#include "Condiments.h"

class HotDog
{
public:
	/* MY CODE */
	/*	Default Constructor	*/
	HotDog();
	/*	Copy Constructor	*/
	HotDog(const HotDog& r);
	/*	Assignment Operator	*/
	HotDog& operator = (const HotDog& r);
	/*	Destructor	*/
	~HotDog();
	/* END OF MY CODE */
	 
	// Public Methods (Required)
	void Minus(const Condiments condiment);
	void Add(const Condiments condiment);

	// Methods for Testing and Internals (Required)
	unsigned int GetCondiments() const;
	HotDog * const GetNext() const;
	HotDog * const GetPrev() const;
	void SetNext(HotDog * const pDog);
	void SetPrev(HotDog * const pDog);
	
	// Debugging
	void Print(int num = -1, int numTabs = 0) const;

private:
	/* MY CODE */
	// use the condiments unsigned integer provided
	// no additional data for condiments
	unsigned int condiments;
	// HotDog pointers for keeping track of next and previous hotdogs in the list
	HotDog* next;
	HotDog* prev;
	/* END OF MY CODE */
};

#endif

//---  End of File ---
