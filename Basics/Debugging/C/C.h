//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef C_H
#define C_H

class Student
{
public:
	Student();
	// FIX: made the Student destructor virtual so the Student created
	// 	when each subsequent child class is created gets properly deleted
	virtual ~Student();

	static char *greeting;
};

class Italian : public Student
{
public:
	Italian();
	virtual ~Italian();
};

class French : public Student
{
public:
	French();
	virtual ~French();
};

class Spanish : public Student
{
public:
	Spanish();
	virtual ~Spanish();
};

#endif

// End of File
