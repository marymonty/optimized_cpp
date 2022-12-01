//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef B_H
#define B_H

class BankHoliday
{
public:
	BankHoliday();
	virtual ~BankHoliday() = default;
	virtual void init() = 0;
};

class StPatricks : public BankHoliday
{
public:
	const char *GetDay();
	// FIX: defined a StPatricks() default constructor
	StPatricks();
	//~StPatricks();

private:
	virtual void init() override;
	const char *day;
};

#endif

// End of File
