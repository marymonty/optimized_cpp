//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef E_H
#define E_H

class Animal
{
public:
	Animal();
	Animal(const Animal & a);

	const char *action;
};

class Dog : public Animal
{
public:
	Dog();
	Dog(const Dog &);

	// cannot change this method
	const char *GetAction(const Dog d);

};

#endif

// End of File