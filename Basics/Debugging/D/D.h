//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef D_H
#define D_H

// ----------------------------------------------------------------------
// Problem 7:
//
// Rules: Fix the code below to have the correct number of components in Car
// ----------------------------------------------------------------------

class Car
{
public:
	Car();
	Car(const Car& c) = default;
	virtual ~Car() = default;
	enum class Color
	{
		Green,
		Yellow,
		Blue,
		Red,
		Black,
		White
	};

	int	numDoors;
	int	wings;
	int	wheelDrive;
	Color color;
};

class Volkswagon : public Car
{
public:
	Volkswagon();
	Volkswagon(const Volkswagon& v) = default;
	virtual ~Volkswagon() = default;
};

class Audi : public Volkswagon
{
public:
	Audi();
	Audi(const Audi& a) = default;
	~Audi() = default;
};

#endif

// End of File
