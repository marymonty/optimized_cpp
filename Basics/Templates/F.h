//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef F_H
#define F_H

// MODIFY this file

// There should be two classes defined in this header
//     Generalized template class
//     Full class specification class 
//
// Generalized: Cut & Paste from E.h for the general class template
//     Then add a second full specialization class
//
// Write a full class specialization for float
//     in this class when you push() a float it pushes the data twice
//     in this class when you pop() it pops a singe element off the stack
//     top() and empty() behave the same.

#include <vector>

template <typename T>
class StackF
{

public:
	// Write the following functions

	// push element
	void push(T const& data)
	{
		this->elems.push_back(data);
	}

	// pop element
	void pop()
	{
		if (!this->elems.empty())
		{
			elems.pop_back();
		}
	}

	// return top element
	T top() const
	{
		// since we're pushing back, the newest element is at the back of the vector
		return elems.back();
	}

	// return whether the stack is empty
	bool empty() const
	{
		return elems.empty();
	}

private:
	std::vector<T> elems;     // elements
};


template<>
class StackF<float>
{
public:
	// Write the following functions

	// push element
	void push(float const & data)
	{
		// push_back twice
		this->elems.push_back(data);
		this->elems.push_back(data);
	}

	// pop element
	void pop()
	{
		if (!this->elems.empty())
		{
			elems.pop_back();
		}
	}

	// return top element
	float top() const
	{
		return elems.back();
	}

	// return whether the stack is empty
	bool empty() const
	{
		return elems.empty();
	}

private:
	std::vector<float> elems;     // elements
};


#endif

// ---  End of File ---------------
