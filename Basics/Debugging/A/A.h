//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_H
#define A_H

class A
{
public:
	A(int val);
	int getFirst();
	int getSecond();
	
private:
	// need to match the order to the initializer list in A.cpp
	int Second;
	int First;
};

#endif

// End of File