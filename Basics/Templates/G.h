//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef G_H
#define G_H

// Change this file
//
// There should be two classes defined in this header
//     Generalized Template class
//     Partial Specialization class
//
// Apppend to the bottom of file

template <typename R, typename S>
class container
{
public:
	const R getData0();
	const S getData1();
	void setData0(const R val);
	void setData1(const S val);

private:
	R rVal;
	S sVal;
};

template <typename R, typename S>
const R container<R, S>::getData0()
{
	return rVal;
}

template <typename R, typename S>
const S container<R, S>::getData1()
{
	return sVal;
}

template <typename R, typename S>
void container<R, S>::setData0(const R val)
{
	this->rVal = val;
}

template <typename R, typename S>
void container<R, S>::setData1(const S val)
{
	this->sVal = val;
}

// Create a partial specializaton on S for second type is int
// In this partial specializaton, have the integer store 3x the input value
//
// ---> add partial specialization below:
template <typename S>
class container<S, int>
{
public:
	const S getData0();
	const int getData1();
	void setData0(const S val);
	void setData1(const int val);

private:
	S sVal;
	int intVal;
};

template <typename S>
const S container<S, int>::getData0()
{
	return sVal;
}

template <typename S>
const int container<S, int>::getData1()
{
	return intVal;
}

template <typename S>
void container<S, int>::setData0(const S val)
{
	this->sVal = val;
}

template <typename S>
void container<S, int>::setData1(const int val)
{
	this->intVal = val*3;
}



#endif

// ---  End of File ---------------
