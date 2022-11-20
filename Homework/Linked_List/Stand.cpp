//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Stand.h"

int Stand::currOrders = 0;
int Stand::peakOrders = 0;

// -----------------------------------------------
// AZUL_REPLACE_ME_STUB
// this is place holder for compiling purposes
// Delete each AZUL_REPLACE_ME_STUB line
// Replace with your own code
// -----------------------------------------------

// Methods

/*	Default Constructor
*	Stand()
*		initializes head to be nullptr (no Orders)
*		initializes currOrders and peakOrders to be 0
*	@params: none
*	@returns: none
*/
Stand::Stand()
{
	this->head = nullptr;
	currOrders = 0;
	peakOrders = 0;
}

/*	Copy Constructor
*	Stand(const Stand& r)
*		DEEP COPIES the input order r's doubly linked list of orders
*			we do not just want to point to r's Orders, we need to make our own copies of each Order
*	@params:
*		r : a const reference to an existing Stand
*	@returns: none
*/
Stand::Stand(const Stand& r)
{
	// if the passed Stand reference has no Orders, set head to nullptr
	if (r.GetOrderHead() == nullptr)
	{
		this->head = nullptr;
	}
	else
	{	// the passed Stand ref has orders, deep copy them all and add to back of linked list
		Order* newHead = new Order(*r.GetOrderHead());
		this->head = newHead;
		//increment the current orders and peak orders
		currOrders++;
		peakOrders++;
		Order* rTraverser = r.GetOrderHead();
		while (rTraverser->GetNext() != nullptr)
		{	// go through r's order list, adding each order to the back of this's list
			rTraverser = rTraverser->GetNext();
			this->Add(rTraverser);
			// increment order counts
			currOrders++;
			peakOrders++;
		}
	}
}

/*	Assignment Operator
*	Stand& operator = (const Stand& r)
*		DEEP COPIES the input order r's doubly linked list of orders
*			we do not just want to point to r's Orders, we need to make our own copies of each Order
*	@params:
*		r : a const reference to an existing Stand
*	@returns: 
*		*this : the value of the Stand that is a replica of r
*/
Stand& Stand::operator = (const Stand& r)
{
	// check if this and r are the same value
	if (this == &r)
	{
		return *this;
	}
	// check if r has no orders, so we can set head to nullptr
	if (r.GetOrderHead() == nullptr)
	{
		this->head = nullptr;
	}
	else
	{	// r has at least one order
		// DEEP copy, so make new orders to add to the end of our head list
		Order* newHead = new Order(*r.GetOrderHead());
		this->head = newHead;
		//increment the order counds
		currOrders++;
		peakOrders++;
		Order* rTraverser = r.GetOrderHead();
		while (rTraverser->GetNext() != nullptr)
		{	// go through r's order list, adding each order to the back of this's list
			rTraverser = rTraverser->GetNext();
			this->Add(rTraverser);
			// increment order counts
			currOrders++;
			peakOrders++;
		}
	}
	return *this;
}

/*	Destructor Operator
*	~Stand()
*		deletes the Stand by, starting with head, going through the doubly linked list
*		of Orders, therefore calling the Order destructor for each order
*	@params: none
*	@returns: none
*/
Stand::~Stand()
{
	//delete all Orders
	Order* current_order = this->head;
	if (current_order != nullptr)
	{	// there are Orders in the head list
		while (current_order->GetNext() != nullptr)
		{	// delete each order as we get to it, the order will then call its own destructor
			current_order = current_order->GetNext();
			delete current_order->GetPrev();
			// decrement current orders with every deletion
			currOrders--;
		}
		delete current_order;
		currOrders--;
	}
}


/*
*	int GetCurrOrders() const
*		returns the current value of currOrders
*	@params: none
*	@returns:
*		currOrders : the global varibale counting the current number of orders in the Stand
*/
int Stand::GetCurrOrders() const
{
	return currOrders;
}

/*
*	int GetPeakOrders() const
*		returns the current value of peakOrders
*	@params: none
*	@returns:
*		peakOrders : the global varibale counting the peak number of orders in the Stand
*/
int Stand::GetPeakOrders() const
{
	return peakOrders;
}

/*
*	Order* const GetHead()
*		returns the current value of head
*	@params: none
*	@returns:
*		this->head : the value of the first Order stored in the Stand
*/
Order * const Stand::GetHead()
{
	return this->head;
}

/*
*	Order* const GetOrderHead() const
*		a const function that returns the current value of head
*	@params: none
*	@returns:
*		this->head : the value of the first Order stored in the Stand
*/
Order* const Stand::GetOrderHead() const
{
	return this->head;
}

/*
*	void Remove(const Name name)
*		searches the doubly linked list stored at head for passed Name name to match the orderName
*		once found, the Order with that name gets deleted (removed from the list)
*	@params:
*		name : an enum of class Name that should match a name of an Order in the Stand list
*	@returns: none
*/
void Stand::Remove(const Name name)
{
	// travel through the list searching for an orderName match to name
	Order* currentOrder = this->head;
	if (currentOrder->GetName() == name)
	{	// the named order is the first order (head)
		if (currentOrder->GetNext() != nullptr)
		{	// there are orders after this first order, so fix pointers
			this->head = currentOrder->GetNext();
			this->head->SetPrev(nullptr);
		}
		else
		{	// there are no other orders, so set to nullptr
			this->head = nullptr;
		}
		// delete the order and decrement currOrders
		delete currentOrder;
		currOrders--;
	}
	else
	{	// the Order match is not found at head
		currentOrder = this->head->GetNext();
		while (currentOrder != nullptr)
		{
			if (currentOrder->GetName() == name)
			{	// found the name order
				// store the prevOrder and nextOrder for readability and clearity
				Order* prevOrder = currentOrder->GetPrev();
				Order* nextOrder = currentOrder->GetNext();
				if (prevOrder != nullptr)
				{	// there is an order before the one we are removing that we need to update
					prevOrder->SetNext(nextOrder);
				}
				if (nextOrder != nullptr)
				{	// there is an order after the one we are removing that we need to update
					nextOrder->SetPrev(prevOrder);
				}
				// delete the order, decrement currOrders, and break from the while loop
				delete currentOrder;
				currOrders--;
				break;
			}
			else
			{	// keep searching for the matching name order
				currentOrder = currentOrder->GetNext();
			}
		}
	}
}

/*
*	void Add(Order* const pOrder)
*		adds the passed Order value to the BACK of the doubly linked list stored at head
*	@params:
*		*pOrder : the Order value that needs to be added to the back of the list
*	@returns: none
*/
void Stand::Add(Order * const pOrder)
{
	assert(pOrder);
	// we are deep copying, but the assignment operator in the Order class takes care of it
	Order* newOrder = pOrder;
	// increment order counts
	currOrders++;
	peakOrders++;
	Order* thisTraverser = this->head;
	if (thisTraverser != nullptr)
	{	// there are Order(s) in the head list already
		while (thisTraverser->GetNext() != nullptr)
		{	// keep going to the next Order to get to the end of the list
			thisTraverser = thisTraverser->GetNext();
		}
		// we should be at the end of the list if we're out of the while loop
		if (thisTraverser != nullptr)
		{	// add the newOrder to the end of the list by fixing pointers
			newOrder->SetPrev(thisTraverser);
			thisTraverser->SetNext(newOrder);
		}
	}
	else
	{
		// this->head is empty, so we set the head to be the newOrder
		this->head = newOrder;
	}
}

//---  End of File ---
