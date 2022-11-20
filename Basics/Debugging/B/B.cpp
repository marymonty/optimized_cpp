//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "B.h"

// ----------------------------------------------------------------------
//
// B - Project
//
// Rules: Fix the code to have the correct day printing for St Pat's day.
//        Please keep the virtual function init() as a restriction
//        You can make this work with a small addition
//
// ----------------------------------------------------------------------

void BankHoliday::init()
{
}

BankHoliday::BankHoliday()
{
	init();
}

StPatricks::StPatricks()
{
	init();
}

void StPatricks::init()
{
	day = "March 17";
}

const char *StPatricks::GetDay()
{
	return this->day;
}

// End of File