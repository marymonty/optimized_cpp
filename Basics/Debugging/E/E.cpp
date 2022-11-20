//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "E.h"	

// ----------------------------------------------------------------------
//
// E - Project
//
// Rules: Dog's don't meow
//        Fix the code to have the dog bark
//		  Nothing can be hard coded
//
// ----------------------------------------------------------------------

Animal::Animal()
	: action("meow")
{
}

Animal::Animal(const Animal & a)
	: action(a.action)
{
}

Dog::Dog()
{
	action = "bark";
}

Dog::Dog(const Dog &)
{
	// since I'm not sure we can just write action = "bark" here too
	// since we are not passing in any accessible dog to copy, we are just
	// making sure "this" dog is properly initialized with the correct action
	*this = Dog();
}

// You cannot modify this method
const char *Dog::GetAction(const Dog d)
{
	return d.action;
}

// End of File