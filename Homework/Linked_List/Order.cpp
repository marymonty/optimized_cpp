//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Order.h"

// -----------------------------------------------
// AZUL_REPLACE_ME_STUB
// this is place holder for compiling purposes
// Delete each AZUL_REPLACE_ME_STUB line
// Replace with your own code
// -----------------------------------------------

// Methods

/*	Default Constructor
*	Order()
*		initializes orderName to be Unknown
*		initializes next and prev pointers to be nullptrs
*		initializes the head HotDog pointer to be nullptr
*	@params: none
*	@returns: none
*/
Order::Order()
{
	this->orderName = Name::Unknown;
	this->next = nullptr;
	this->prev = nullptr;
	this->head = nullptr;
}

/*	Specialized Constructor
*	Order(Name name)
*		takes a Name enum as input
*		intializes orderName to be name input
*		initializes next and prev pointers to be nullptrs
*		initializes the head HotDog pointer to be nullptr
*	@params: 
*		name : an enum of class Name
*	@returns: none
*/
Order::Order(Name name)
{
	this->orderName = name;
	this->next = nullptr;
	this->prev = nullptr;
	this->head = nullptr;
}

/*	Copy Constructor
*	Order(const Order& r)
*		copies the initialized orderName from input Order r to calling Order this
*		initialized the next and previous pointers to be nullptr
*			we do not want to initialized them with r's pointers because this copy is not
*			auto put into the doubly linked list
*		DEEP COPIES the input order r's HotDogs
*			we do not just want to point to r's HotDogs, we need to make our own copies of each dog
*	@params:
*		r : a const reference to an existing Order
*	@returns: none
*/
Order::Order(const Order& r)
{
	this->orderName = r.orderName;
	this->next = nullptr;
	this->prev = nullptr;
	// if r has no HotDogs in their Order, we set head to nullptr
	if (r.GetHead() == nullptr)
	{
		this->head = nullptr;
	}
	else
	{	//r has HotDogs in their Order, we need to Deep Copy
		HotDog* newHead = new HotDog(*r.GetHead());
		this->head = newHead;
		HotDog* rTraverser = r.GetHead();
		while (rTraverser->GetNext() != nullptr)
		{
			// traverse the linked list making new HotDogs and adding them 
			// TO THE END OF THE HOTDOG LIST using AddToBack
			rTraverser = rTraverser->GetNext();
			this->AddToBack(rTraverser);			
		}
	}	
}

/*	Assignment Operator
*	Order& operator = (const Order& r)
*		sets the calling Order (this) to be equal to the passed reference Order r
*		copies the initialized orderName from input Order r to calling Order this
*		initialized the next and previous pointers to be nullptr
*			we do not want to initialized them with r's pointers because this copy is not
*			auto put into the doubly linked list
*		DEEP COPIES the input order r's HotDogs
*			we do not just want to point to r's HotDogs, we need to make our own copies of each dog
*	@params:
*		r : a const reference to an existing Order
*	@returns: 
*		*this : an Order value of a replica Order r
*/
Order& Order::operator = (const Order& r)
{
	// check if the Order*'s are already pointing to the same Order
	if (this == &r)
	{
		return *this;
	}
	this->orderName = r.orderName;
	this->next = nullptr;
	this->prev = nullptr;
	// if r has no HotDogs in their Order, we set head to nullptr
	if (r.GetHead() == nullptr)
	{
		this->head = nullptr;
	}
	else
	{	//r has HotDogs in their Order, we need to Deep Copy
		HotDog* newHead = new HotDog(*r.GetHead());
		this->head = newHead;
		HotDog* rTraverser = r.GetHead();
		while (rTraverser->GetNext() != nullptr)
		{
			// traverse the linked list making new HotDogs and adding them 
			// TO THE END OF THE HOTDOG LIST using AddToBack
			rTraverser = rTraverser->GetNext();
			this->AddToBack(rTraverser);
		}
	}
	return *this;
}

/*	Destructor Operator
*	~Order()
*		deletes the Order by, starting with head, going through the doubly linked list
*		of HotDogs, deleting each HotDog as we go
*	@params: none
*	@returns: none
*/
Order::~Order()
{	
	//	delete all hotdogs
	// start with a HotDog to traverse the list with
	HotDog* current_dog = this->head;
	if (current_dog != nullptr)
	{
		while (current_dog->GetNext() != nullptr)
		{
			// delete a hotdog as soon as we get to it
			current_dog = current_dog->GetNext();
			delete current_dog->GetPrev();
		}
		delete current_dog;
	}
	
}


/*
*	void Add(HotDog *p)
*		adds the passed HotDog value to the front of the doubly linked list stored at head
*	@params:
*		*p : the HotDog value that needs to be added to the front of the list
*	@returns: none
*/
void Order::Add(HotDog *p)
{
	assert(p);
	HotDog* newDog = p;
	if (this->head == nullptr)
	{	// there is no HotDog yet in the Orders list, so this HotDog p is the head
		this->head = newDog;
		newDog->SetNext(nullptr);
		newDog->SetPrev(nullptr);
	}
	else
	{	// there are HotDogs in the Orders list, so put this one at the front
		// and have the old head point prev to this newDog 
		// and this newDog point next to the old head
		this->head->SetPrev(newDog);
		newDog->SetNext(this->head);
		newDog->SetPrev(nullptr);
		this->head = newDog;
	}
}

/*
*	void AddToBack(HotDog *p)
*		adds the passed HotDog value to the BACK of the doubly linked list stored at head
*	@params:
*		*p : the HotDog value that needs to be added to the back of the list
*	@returns: none
*/
void Order::AddToBack(HotDog* p)
{
	assert(p);
	// create a newDog to add to the list
	HotDog* newDog = new HotDog(*p);
	HotDog* thisTraverser = this->head;
	if (thisTraverser != nullptr)
	{	// use while loop to get to the final HotDog of the linked list
		while (thisTraverser->GetNext() != nullptr)
		{
			thisTraverser = thisTraverser->GetNext();
		}
		// set the final HotDog (thisTraverser) to point next to the newDog
		// and set newDog prev to point to this last HotDog
		if (thisTraverser != nullptr)
		{
			newDog->SetPrev(thisTraverser);
			thisTraverser->SetNext(newDog);
		}
	}
	else
	{	// this->head is empty so the back of the list is still the head
		this->head = newDog;
	}
}

/*
*	void Remove(HotDog *p)
*		searches the doubly linked list stored at head for passed HotDog p
*		once found, HotDog p gets deleted (removed from the list)
*	@params:
*		*p : the HotDog value that needs to be removed from the list
*	@returns: none
*/
void Order::Remove(HotDog *p)
{
	assert(p);
	HotDog* currentDog = this->head;
	// starting with head, check to see if the currentDog == p
	if (currentDog == p)
	{	// found the match to p
		if (currentDog->GetNext() != nullptr)
		{	// p is the head, so reset the head pointer to be the next HotDog in the list
			this->head = currentDog->GetNext();
			this->head->SetPrev(nullptr);
		}
		else
		{	// there is no next HotDog in the list, so the head is nullptr
			this->head = nullptr;
		}
		// either way, delete currentDog
		delete currentDog;
	}
	
	else
	{	// p is not the head, so use currentDog to keep looking through the list for a match
		currentDog = this->head->GetNext();
		while (currentDog != nullptr)
		{
			if (currentDog == p)
			{	// we found the match
				// storing the prev dog and next dog for code clarity when removing a middle HotDog
				HotDog* prevDog = currentDog->GetPrev();
				HotDog* nextDog = currentDog->GetNext();
				// check for nullptrs, but set the prev and next pointers to skip over HotDog we are removing
				if (prevDog != nullptr)
				{
					prevDog->SetNext(nextDog);
				}
				if (nextDog != nullptr) 
				{
					nextDog->SetPrev(prevDog);
				}
				// delete the dog and stop the while loop
				delete currentDog;
				break;
			}
			else
			{	// we have not found the match, keep traversing
				currentDog = currentDog->GetNext();
			}
		}
	}
}


/*
*	Order* const GetNext() const
*		returns the pointer pointing to the next Order in the doubly linked list
*	@params: none
*	@returns:
*		this->next : the Order* pointing to the next Order
*/
Order * const Order::GetNext() const
{
	return this->next;
}

/*
*	Order* const GetPrev() const
*		returns the pointer pointing to the previous Order in the doubly linked list
*	@params: none
*	@returns:
*		this->prev : the Order* pointing to the prev Order
*/
Order * const Order::GetPrev() const
{
	return this->prev;
}

/*
*	HotDog* const GetHead() const
*		returns the pointer pointing to the first HotDog in the Order's doubly linked list head
*	@params: none
*	@returns:
*		this->head : the HotDog* pointing to the first head HotDog
*/
HotDog * const Order::GetHead() const
{
	return this->head;
}

/*
*	void SetNext(Order *p)
*		sets the calling Order's next pointer to point to the input Order - p
*		also sets the input Order's prev pointer to point to the calling Order (this)
*	@params:
*		*p : the Order value that we are adding to the list by pointing to it
*	@returns: none
*/
void Order::SetNext(Order *p)
{
	if (p != nullptr)
	{
		this->next = p;
		p->prev = this;
	}
	else
	{
		this->next = nullptr;
	}
}

/*
*	void SetPrev(Order *p)
*		sets the calling Order's prev pointer to point to the input Order - p
*		also sets the input Order's next pointer to point to the calling Order (this)
*	@params:
*		*p : the Order value that we are adding to the list by pointing to it
*	@returns: none
*/
void Order::SetPrev(Order *p)
{
	if (p != nullptr)
	{
		this->prev = p;
		p->next = this;
	}
	else
	{
		this->prev = nullptr;
	}
}

/*
*	Name GetName() const
*		returns the Name enum stored for the Order
*	@params: none
*	@returns:
*		this->orderName : the enum of class Name, the name of the order
*/
Name Order::GetName() const
{
	return this->orderName;
}

/*
*	Name SetName() const
*		sets the Name enum stored for the Order
*	@params: 
*		name : the enum of class Name to store in orderName
*	@returns: none
*/
void Order::SetName(Name name)
{
	this->orderName = name;
}

//---  End of File ---
