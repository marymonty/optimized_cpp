//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef STAND_H
#define STAND_H

// Add files include as needed
#include "Names.h"
#include "Order.h"

class Stand
{
public:
	/* MY CODE */
	/*	Default Constructor	*/
	Stand();
	/*	Copy Constructor	*/
	Stand(const Stand& r);
	/*	Assignment Operator	*/
	Stand& operator = (const Stand& r);
	/*	Destructor	*/
	~Stand();
	/* END OF MY CODE */

	// Public Methods (Required)
	void Remove(const Name name);
	void Add(Order * const pOrder);
	int GetCurrOrders() const;
	int GetPeakOrders() const;
	
	// Methods used for Testing and Internals (Required)
	Order * const GetHead();
	
	/* MY METHOD : added my own const GetHead method, GetOrderHead(), to use in Stand.cpp */
	Order* const GetOrderHead() const;

	// global variables, increment in Stand.cpp when Orders are created
	static int currOrders;
	static int peakOrders;

private:
	/* MY CODE */
	// only data needed is head, an Order pointer to store the first order in the doubly linked list
	Order* head;
	/* END OF MY CODE */
};

#endif

//---  End of File ---
