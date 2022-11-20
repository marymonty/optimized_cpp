//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "HotDog.h"

// -----------------------------------------------
// AZUL_REPLACE_ME_STUB
// this is place holder for compiling purposes
// Delete each AZUL_REPLACE_ME_STUB line
// Replace with your own code
// -----------------------------------------------

// Methods

/*
*	void Minus(const Condiments condiment)
*		uses bitwise manipulation (bitwise AND) to remove a specified condiment from the HotDog
*		need to cast everything to unsigned ints to do the bitwise manipulation
*	@params:
*		condiment : of the Condiment class, an enum of a particular condiment
*	@returns: none
*/
void HotDog::Minus(const Condiments condiment)
{
	unsigned int old_condi = this->condiments;
	// we need to use bitwise NOT (~) to invert the bits to create holes in the proper spaces
	unsigned int remove_condi = ~(unsigned int)condiment;
	// & = bitwise AND
	old_condi = (unsigned int)(old_condi & remove_condi);
	this->condiments = old_condi;
}

/*
*	void Add(const Condiments condiment)
*		uses bitwise manipulation (bitwise OR) to add a specified condiment to the HotDog
*		need to cast everything to unsigned ints to do the bitwise manipulation
*	@params:
*		condiment : of the Condiment class, an enum of a particular condiment
*	@returns: none
*/
void HotDog::Add(const Condiments condiment)
{
	unsigned int old_condi = this->condiments;
	unsigned int new_condi = (unsigned int)condiment;
	// | = bitwise OR
	old_condi = (unsigned int)(old_condi | new_condi);
	this->condiments = old_condi;
}


/*	Default Constructor
*	HotDog()
*		initializes condiments to unsigned int 0
*		initializes next and prev pointers to be nullptrs
*	@params: none
*	@returns: none
*/
HotDog::HotDog()
{
	this->condiments = (unsigned int)0;
	this->next = nullptr;
	this->prev = nullptr;

}

/*	Copy Constructor
*	HotDog(const HotDog& r)
*		copies the initialized condiment from input hotdog r to calling hotdog this
*		still initialized the next and previous pointers to be nullptr
*			we do not want to initialized them with r's pointers because this copy is not
*			auto put into the doubly linked list
*	@params:
*		r : a const reference to an existing HotDog
*	@returns: none
*/
HotDog::HotDog(const HotDog& r)
{
	this->condiments = r.condiments;
	// do not copy over the pointers
	this->next = nullptr;
	this->prev = nullptr;
}

/*	Assignment Operator
*	operator = (const HotDog& r)
*		sets a HotDog object to be equal to the passed referenced HotDog object
*		like the copy constructor, do not set the next and prev pointers
*	@params:
*		r : a reference to an existing const HotDog object
*	@returns:
*		HotDog& : a reference to a set HotDog object
*/
HotDog& HotDog::operator = (const HotDog& r)
{
	if (this == &r) 
	{
		return *this;
	}
	this->condiments = r.condiments;
	// do not copy over the pointers
	this->next = nullptr;
	this->prev = nullptr;
	return *this;
}

/*	Destructor Operator
*	~HotDog()
*		deletes the HotDog by doing nothing
*	@params: none
*	@returns: none
*/
HotDog::~HotDog()
{
	//do nothing
}


/*
*	unsigned int GetCondiments() const
*		returns the condiments belonging to the calling HotDog (this)
*	@params: none
*	@returns: 
*		this->condiments : the HotDog's condiments, as an unsigned int
*/
unsigned int HotDog::GetCondiments() const
{
	return this->condiments;
}

/*
*	HotDog* const GetNext() const
*		returns the pointer pointing to the next HotDog in the doubly linked list
*	@params: none
*	@returns:
*		this->next : the HotDog* pointing to the next HotDog 
*/
HotDog * const HotDog::GetNext() const
{
	if (this->next == nullptr)
	{
		return nullptr;
	}
	return this->next;
}

/*
*	HotDog* const GetPrev() const
*		returns the pointer pointing to the previous HotDog in the doubly linked list
*	@params: none
*	@returns:
*		this->prev : the HotDog* pointing to the prev HotDog
*/
HotDog * const HotDog::GetPrev() const
{
	if (this->prev == nullptr)
	{
		return nullptr;
	}
	return this->prev;
}

/*
*	void SetNext(HotDog *pDog)
*		sets the calling HotDog's next pointer to point to the input HotDog - pDog
*		also sets the input HotDog's prev pointer to point to the calling HotDog (this)
*	@params: 
*		*pDog : the HotDog value that we are adding to the list by pointing to it
*	@returns: none
*/
void HotDog::SetNext(HotDog *pDog)
{
	if (pDog != nullptr)
	{
		this->next = pDog;
		pDog->prev = this;
	}
	else
	{
		this->next = nullptr;
	}
	
}

/*
*	void SetPrev(HotDog *pDog)
*		sets the calling HotDog's prev pointer to point to the input HotDog - pDog
*		also sets the input HotDog's next pointer to point to the calling HotDog (this)
*	@params:
*		*pDog : the HotDog value that we are adding to the list by pointing to it
*	@returns: none
*/
void HotDog::SetPrev(HotDog *pDog)
{
	if (pDog != nullptr)
	{
		this->prev = pDog;
		pDog->next = this;
	}
	else
	{
		this->prev = nullptr;
	}
	
}


// ---  End of File ---------------

