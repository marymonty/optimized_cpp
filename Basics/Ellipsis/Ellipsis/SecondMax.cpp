//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <vector>
#include <algorithm>

#include "SecondMax.h"

/* MY CODE */
int SecondMax(int count, ...)
{
	// we access the ellipsis using va_list
	// this is part of <cstdarg>, it is of type list
	// and we can use it to traverse the ellipsis argument
	va_list argList;
	// get to the start of argList with va_start
	// its parameters are the list itself, and the last non-ellipsis param
	va_start(argList, count);

	std::vector<int> intVect;
	//Trace::out("count = %i\n", count);
	int i = 0;
	while (i < count)
	{
		// va_arg returns the value the list is referring to
		// arguments are the list and what type the parameter we are getting is
		// it also moves va_list automatically to the next param
		intVect.push_back(static_cast<int>va_arg(argList, int));
		i++;
	}
	// close the argList
	va_end(argList);

	// sort the vector (in ascending order)
	std::sort(intVect.begin(), intVect.end());
	int returnInt = -1;
	// store the largest int as the last index
	int largestInt = intVect[intVect.size()-1];
	// start at one before the end of the list then move backwards
	size_t j = (intVect.size() - 1);
	while (j >= 0)
	{
		// check if the int at index j is smaller than the largestInt (last index)
		if (intVect[j] < largestInt)
		{
			// it is so this is the number we return
			returnInt = intVect[j];
			break;
		}
		// this index is still equal to the largestInt so keep moving in reverse 
		j--;
	}
	//printVect(intVect);

	return returnInt;
}

// quick helper function to print the vector
const void printVect(const std::vector<int> intVect)
{
	unsigned int j = 0;
	Trace::out("intVect size = %i\n", intVect.size());
	Trace::out(" \t\t Vector :\n");
	while (j < intVect.size())
	{
		Trace::out("\t\t %i \n", intVect[j]);
		j++;
	}
}

/* END OF MY CODE */

// ---  End of File ---------------
