//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Monkey.h"

// Global variables - incremented when status char *'s are created and destroyed
int Monkey::numStringsCreated = 0;
int Monkey::numStringsDestroyed = 0;


/* my code */

/*	Default Constructor
*	Monkey()
*		initializes x to 878
*		initializes y to 979
*		initializes pStatus to "This string was initialized by a default constructor!"
*			therefore increments the numStringsCreated
*	@params: none
*	@returns: none
*/
Monkey::Monkey() 
{
	this->x = 878;
	this->y = 979;
	//must create a new char* 
	size_t status_length = strlen("This string was initialized by a default constructor!") + 1;
	this->pStatus = new char[status_length];
	strcpy_s(pStatus, status_length, "This string was initialized by a default constructor!");
	//increment numStringsCreated
	numStringsCreated++;
}

/*	Specialized Constructor
*	Monkey(int _x, int _y)
*		takes input for the int values of x and y
*		sets the status char string as well
*		in the header file _y is set to default to 575
*		trying to redeclare the default 575 here throws an error
*	@params:
*		_x : the value of x given by the calling function
*		_y : the value of y given by the calling function, defaults to 575 if no _y is given
*	@returns: none
*/
Monkey::Monkey(int _x, int _y)
{
	this->x = _x;
	this->y = _y;
	size_t status_length = strlen("ThIs tring was initilizxd by a clever user!") + 1;
	this->pStatus = new char[status_length];
	strcpy_s(pStatus, status_length, "ThIs tring was initilizxd by a clever user!");
	//increment numStringsCreated
	numStringsCreated++;
}

/*	Copy Constructor
*	Monkey(const Monkey& r)
*		copies the initialized x and y ints
*		deep copies the string
*	@params: 
*		r : a const reference to an existing Monkey
*	@returns: none
*/
Monkey::Monkey(const Monkey& r)
{
	this->x = r.x;
	this->y = r.y;
	size_t status_length = strlen(r.pStatus) + 1;
	this->pStatus = new char[status_length];
	strcpy_s(pStatus, status_length, r.pStatus);
	numStringsCreated++;
}

/*	Assignment Operator
*	operator = (const Monkey& r)
*		sets a Monkey object to be equal to the passed referenced Monkey object
*	@params:
*		r : a reference to an existing const Monkey object
*	@returns:
*		Monkey& : a reference to a Monkey object
*/
Monkey& Monkey::operator = (const Monkey& r)
{
	// first we check to see if the referenced Monkey and this are the same
	if (this == &r) {
		return *this;
	}
	// if not the same, set this's variables
	this->x = r.x;
	this->y = r.y;
	// delete the status currently at this's pStatus
	delete this->pStatus;
	numStringsDestroyed++;
	// set the new pStatus for this
	size_t status_length = strlen(r.pStatus) + 1;
	this->pStatus = new char[status_length];
	strcpy_s(pStatus, status_length, r.pStatus);
	numStringsCreated++;
	 

	return *this;
}

/*	Destructor Operator
*	~Monkey()
*		deletes the char* that is pStatus
*		therefore, incrementing the numStringsDestoryed
*	@params: none
*	@returns: none
*/
Monkey::~Monkey()
{
	//delete the created char*
	delete this->pStatus;
	//increment numStringsDestroyed
	numStringsDestroyed++;
}


/* end my code, however I did add comments for all functions below */


/*
*	int getX()
*		returns the value stored in this Monkey's x
*	@params: none
*	@returns:
*		this->x : the int value stored in x
*/
int Monkey::getX()
{
	return this->x;
}

/*
*	int getY()
*		returns the value stored in this Monkey's y
*	@params: none
*	@returns:
*		this->y : the int value stored in y
*/
int Monkey::getY()
{
	return this->y;
}

/*
*	char * getStatus()
*		returns the char * stored in this Monkey's status
*	@params: none
*	@returns:
*		this->pStatus : the char * stored in pStatus
*/
char *Monkey::getStatus()
{
	return this->pStatus;
};

/*
*	void printStatus()
*		prints a formatted char * of this Monkey's pStatus
*	@params: none
*	@returns: none
*/
void Monkey::printStatus()
{
	Trace::out("Monkey (Status): %s\n", this->pStatus);
}


//---  End of File ---
