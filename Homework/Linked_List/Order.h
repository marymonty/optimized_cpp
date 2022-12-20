//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ORDER_H
#define ORDER_H

// Add files include as needed
#include "HotDog.h"
#include "Names.h"

class Order 
{
public:
	/* MY CODE */
	/*	Default Constructor	*/
	Order();
	/*	Copy Constructor	*/
	Order(const Order& r);
	/*	Assignment Operator	*/
	Order& operator = (const Order& r);
	/*	Destructor	*/
	~Order();
	/* END OF MY CODE */

	// Public Methods (Required)
	Order(const Name name);
	Name GetName() const;
	void SetName(const Name name);
	void Add(HotDog * const pDog);
	void AddToBack(HotDog* const pDog);
	void Remove(HotDog * const pDog);

	// Methods used for Testing and Internals (Required)
	HotDog * const GetHead() const;
	Order * const GetNext() const;
	Order * const GetPrev() const;
	void SetNext(Order * const pOrder);
	void SetPrev(Order * const pOrder);


private:
	/* MY CODE */
	// orderName : an enum of type Name class
	Name orderName;
	// Order pointers to store the next and previous Orders for a doubly linked list
	Order* next;
	Order* prev;
	// HotDog pointer to store the first (head) HotDog in each Order
	HotDog* head;
	/* END OF MY CODE */
};

#endif

//---  End of File ---
