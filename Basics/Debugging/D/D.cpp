//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "D.h"

// ----------------------------------------------------------------------
//
// D - Project
//
// Rules: Fix the code below to have the correct number of components in Car
//
// ----------------------------------------------------------------------

// need to initialize wings somewhere
Car::Car()
{
	wings = 0;
}

Volkswagon::Volkswagon()
{
	wheelDrive = 2;
	numDoors = 4;
}

Audi::Audi()
{
	color = Color::Black;
	wheelDrive += 2;
}

// End of File