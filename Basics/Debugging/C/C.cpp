//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "C.h"

// ----------------------------------------------------------------------
//
// C - Project
//
// Rules: fix the classes to make the function work as intended
//        construction of the object should print "Hello"
//        destruction of the object should print "Goodbye"
//        in the appropriate language
//
// ----------------------------------------------------------------------

char *Student::greeting = 0;

Student::Student()
{
	Student::greeting = 0;
}

Student::~Student()
{
}

Italian::Italian()
{
	greeting = "Ciao!";
}

Italian:: ~Italian()
{
	greeting = "Arrivederci!";
}

French::French()
{
	greeting = "Bonjour!";
}

French :: ~French()
{
	greeting = "Au revoir!";
}

Spanish::Spanish()
{
	greeting = "Hola!";
}

Spanish :: ~Spanish()
{
	greeting = "Adios!";
}

// End of File
