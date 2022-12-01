//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef J_H
#define J_H

class Dog
{
public:
	int *pVal;
	// FIX: declare the "big four" (default constructor, copy constructor,
	//	assignment operator, and destructor) and make any possible default
	Dog() = default;
	Dog(int val);
	Dog(const Dog& d);
	Dog& operator=(const Dog& d) = default;
	~Dog();

	static int GetVal(Dog d);
};

#endif

// End of File
