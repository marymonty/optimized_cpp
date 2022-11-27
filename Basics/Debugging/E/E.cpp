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
	// FIX: make sure "this" dog is properly initialzied with the correct action
	// since we are not passing in any accessible dog to copy
	*this = Dog();
}

// You cannot modify this method
const char *Dog::GetAction(const Dog d)
{
	return d.action;
}

// End of File
