//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Nyble.h"

/**********************	My OWN HELPER FUNCTIONS	**************************/

/*
*	findBinary(unsigned char input_char)
*		find the 4 bit binary version of our input_char
*		We are taking numbers in binary and making sure they stay as 4bit
*		So what that means is we have our numbers:
*			1 : 0001
*			2 : 0010
*			3 : 0011
*			etc...
*			15: 1111
*			16: would be 10000, but we are keeping everything to 4 bits so 
*			16: 0000
*			17: 0001
*			etc.
*		to find these numbers we use bitwise AND (&) on the input number & 0xf (1111)
*			input = 18 : 10010 &
*					f  : 01111 = 
*					2  : 00010 
*	@params:
*		input_char : the unsigned char we need to make sure is in 4 bit
*	@returns:
*		return_val : an unsigned char equal to the 4 bit version of our input char
*/
unsigned char findBinary(unsigned char input_char)
{
	unsigned char return_val = 0;
	int in_char = int(input_char);
	// Bitwise AND with 0xf (1111) 
	in_char = in_char & 0x0f;
	// now in_char is 15 or less
	return_val = (unsigned char)in_char;
	return return_val;
}


/*
*	bitShift(unsigned char input_char)
*		bitShift finds if the bit shifted left in the << operator function was a 1 or a 0.
* 
*		the rotational shift function, helper to the << function
*		each bit has rotated to the left by the number specified in the << function
*		if a bit falls off the edge, it is rotated to the beginning
*		So what that means is we have our numbers:
*			1 : 0001
*			2 : 0010
*			3 : 0011
*			etc...
*			13: 1101
*			14: 1110
*			15: 1111
*			so if we bit shift 13 by 1 it would go from 1101 to 101_ where the _ would 
*			be filled in with the shifted out bit, in this case that first 1
*		We find if the shifted bit was a 1 or 0 by shifting the number left 1, then 
*		shifting right 4, so the number that was originally shifted left is now in the first 
*		bit spot. We can easily tell if this is a 1 or 0 by checking if its odd or even.
*			input = 13 :   1101
*				13 << 1 = 11010 or 26
*				26 >> 4 = 00001 or 1
*			so we pass back a 1 to add to the shifted bits!
*	@params:
*		input_char : the unsigned char we are shifting
*	@returns:
*		return_val : a 1 or a 0 depending on the shifted bit
*/

unsigned char bitShift(unsigned char input_char)
{
	unsigned char return_val = 0;
	int in_char = int(input_char);
	// shift left by 1 bit
	in_char = in_char << 1;
	//shift right by 4 bits to find the bit lost in the 1 bit shift
	in_char = in_char >> 4;
	//check if the bit shifted was a 1 or a 0 by checking odd or even
	if (in_char % 2 != 0)
	{	//the bit shifted was a 1
		return_val = 1;
	}
	return return_val;
}

/********************	BIG FOUR	************************/

/*	Default Constructor	
*		initializes data to be an unsigned char 0
*	@params: none
*	@returns: none
*/
Nyble::Nyble()
{
	this->data = (unsigned char) 0;
}

/*	Specialized Constructor	
*		makes sure the unsigned char input is only 4 bits
*		initializes data to be the fixed unsigned char c
*	@params: 
*		c : the unsigned char to set this->data to once in 4 bit form
*	@returns: none
*/
Nyble::Nyble(const unsigned char c) 
{
	unsigned char c_new = findBinary(c);
	this->data = c_new;
}

/*	Specialized Constructor
*		makes sure the unsigned int input is only 4 bits
*		initializes data to be the fixed unsigned int (casted as unsigned char) c
*	@params:
*		c : the unsigned int (casted unsigned char) to set this->data to once in 4 bit form
*	@returns: none
*/
Nyble::Nyble(const unsigned int i)
{
	unsigned char input_char = (unsigned char)i;
	input_char = findBinary(input_char);

	this->data = (unsigned char) input_char;
}

/*	Specialized Constructor
*		makes sure the int input is only 4 bits
*		initializes data to be the fixed int (casted as unsigned char) c
*	@params:
*		c : the int (casted unsigned char) to set this->data to once in 4 bit form
*	@returns: none
*/
Nyble::Nyble(const int i)
{
	unsigned char input_char = (unsigned char)i;
	input_char = findBinary(input_char);

	this->data = (unsigned char)input_char;
}

/*	Copy Constructor	
*		initialized this's data with the same data as from the passed referenced Nyble
*	@params: 
*		r : a const reference to the Nyble we are copying
*	@returns: none
*/
Nyble::Nyble(const Nyble& r)
{
	this->data = r.data;
}

/*	Assignment Operator	
*		initialized this's data with the same data as from the passed referenced Nyble
*	@params:
*		r : a const reference to the Nyble we are copying
*	@returns:
*		*this : the value of the Nyble with newly assigned data
*/
Nyble& Nyble::operator = (const Nyble& r)
{
	// first we check to see if the referenced Nyble and this are the same
	if (this == &r) {
		return *this;
	}
	// if not the same, set this's variables
	this->data = r.data;
	return *this;
}

/*	Destructor
		destroy the current Nyble
	@params: none
	@returns: none
*/
Nyble::~Nyble()
{
	//nothing needed
}


/*************************	BINARY OPERATORS	**************************/

/*	Nyble operator + (const int& c)
*		Nyble + int
*	@params: 
*		c : a const int to add to the calling Nyble
*	@returns:
*		Nyble::Nyble(new_data) : a scoped Nyble constructing a Nyble with the added
*			sum of the Nyble's data + param c
*/
Nyble Nyble::operator + (const int& c)
{
	int current_data = (int)this->data;
	current_data += c;
	unsigned char new_data = (unsigned char)current_data;
	return Nyble::Nyble(new_data);
}

/*	Nyble operator + (const int& r, const Nyble& s)
*		int + Nyble
*	@params:
*		r : a const int 
*		s : a const Nyble
*	@returns:
*		Nyble::Nyble(new_data) : a scoped Nyble constructing a Nyble with the added
*			sum of param r + param s
*/
Nyble operator + (const int& r, const Nyble& s)
{
	int current_data = (int)s.data;
	current_data += r;
	unsigned char new_data = (unsigned char)current_data;
	return Nyble::Nyble(new_data);
}

/*	Nyble operator + (const Nyble& r)
*		Nyble + Nyble
*	@params:
*		r : a const Nyble to add to the calling Nyble
*	@returns:
*		Nyble::Nyble(new_data) : a scoped Nyble constructing a Nyble with the added
*			sum of the Nyble's data + param r's data
*/
Nyble Nyble::operator + (const Nyble& r)
{
	int current_data = (int)this->data;
	int other_data = (int)r.data;
	current_data += other_data;
	unsigned char new_data = (unsigned char)current_data;
	return Nyble::Nyble(new_data);
}

/*	Nyble operator += (const Nyble& r)
*		Nyble += Nyble
*	@params:
*		r : a const Nyble to add to the calling Nyble
*	@returns:
*		*this : a pointer to the Nyble that just added the
*			param r's data to itself
*/
Nyble Nyble::operator += (const Nyble& r)
{
	int current_data = (int)this->data;
	int other_data = (int)r.data;
	current_data += other_data;
	unsigned char new_data = (unsigned char)current_data;
	new_data = findBinary(new_data);
	this->data = new_data;
	return *this;
}


/************************	UNARY OPERATORS	****************************/

/*	pre-increment
*		Nyble& operator++(Nyble& r)
*		called with ++Nyble	
*	@params:
*		r : the Nyble reference that gets incremented
*	@returns:
*		r : a reference to the same Nyble now incremented once
*/
Nyble& operator++(Nyble& r)
{
	unsigned char orig_num = r.getData();
	unsigned int num_plus = (unsigned int)orig_num + 1;
	unsigned char new_num = (unsigned char)num_plus;
	new_num = findBinary(new_num);
	r.setData(new_num);
	return r;
}

/*	post-increment
*		Nyble operator++(Nyble& r, int unused)
*		called with Nyble++
*		returns a copy of the original value
*		(we need the unused int in the declaration even though we dont use it)
*	@params:
*		r : a Nyble reference, what is being incremented
*		unused : an unused int
*	@returns:
*		Nyble::Nyble(orig_num) : a Nyble constructed with the original value pre-increment
*/
Nyble operator++(Nyble& r, int unused)
{
	// I think the purpose of unused is we could do A++2, but that is irrelevant for this assignment
	unused = 1;
	unsigned char orig_num = r.getData();
	unsigned int num_plus = (unsigned int)orig_num + 1;
	unsigned char new_num = (unsigned char)num_plus;
	new_num = findBinary(new_num);
	r.setData(new_num);
	return Nyble::Nyble(orig_num);
}

/*	left shift - or our rotational bit shift function
*		Nyble operator <<(const Nyble& r, const int times_shifted)
*		called with Nyble << 1
*		bit shifts the Nyble bits in a rotational pattern times_shifted # of times  
*		(brings shifted bits back to the beginning bit)
*	@params:
*		r : the const reference to a Nyble whose bits we are shifting
*		times_shifted : the amount of times we are bit shifting (how many bits shifted)
*	@returns:
*		Nyble::Nyble(left_char) : a Nyble construction called with left_char, the 
*			rotated bit shifted unsigned char
*/
Nyble operator<<(const Nyble& r, const int times_shifted)
{
	unsigned char left_char = r.getNybleData();
	unsigned char moved_bit = 0;
	unsigned int left_num;
	unsigned int moved_bit_int;
	int shift = 0;
	while (shift < times_shifted)
	{
		//bitShift will return a 1 or 0 depending on the shifted bit
		moved_bit = bitShift(left_char);
		moved_bit_int = (unsigned int)moved_bit;
		left_num = (unsigned int)left_char;
		left_num = left_num << 1;
		left_num += moved_bit_int;
		left_char = (unsigned char)left_num;
		shift++;
	}
	// call findBinary after all bits have been rotated to fix to 4 bits
	left_char = findBinary(left_char);
	return Nyble::Nyble(left_char);
}

/*	bitwise compliment (bitwise NOT)
*		Nyble operator~(const Nyble& r)
*		called with ~Nyble
*		inverse the Nyble data (1101 -> 0010)
*	@params:
*		r : const Nyble reference that is getting the bitwise NOT
*	@returns:
*		Nyble::Nyble(not_char) : a Nyble construction called with not_char,
*			which is the 4-bit inverse of param r's data
*/
Nyble operator~(const Nyble& r)
{
	unsigned char new_data = r.getNybleData();
	new_data = findBinary(new_data);
	const unsigned int not_data = ~(unsigned int)new_data;
	unsigned char not_char = (unsigned char)not_data;
	return Nyble::Nyble(not_char);
}

/*	value + 3
*		Nyble operator+(Nyble& r)
*		called with +Nyble
*		adds 3 to the Nyble's data value
*	@params:
*		r : a const Nyble reference whose data is being added with 3
*	@returns:
*		Nyble::Nyble(new_data) : a Nyble construction call using new_data, 
*			the Nybles old data + 3.
*/ 
Nyble operator+(Nyble& r)
{
	unsigned char new_data = r.getNybleData();
	unsigned int num_data = (unsigned int)new_data;
	num_data += 3;
	new_data = (unsigned char)num_data;
	new_data = findBinary(new_data);
	return Nyble::Nyble(new_data);
}

/*	casting operator to unsigned int
*		operator unsigned int()
*		called with unsigned int = Nyble
*		explicitly casts a Nyble to an unsigned int
*	@params: none
*	@returns: 
*		data_int : the calling Nyble's data as an unsigned int
*/
Nyble::operator unsigned int()
{
	unsigned char data_char = this->getNybleData();
	unsigned int data_int = (unsigned int)data_char;
	data_int -= 3;
	return data_int;
}


/*	unsigned char getData()
*		given accessor method
*		returns the calling Nyble's data
*	@params: none
*	@returns:
*		this->data : the calling Nyble's data
*/
unsigned char Nyble::getData()
{
	return this->data;
}

/*	unsigned char const getNybleData() const
*		a const method for accessing a calling Nybles data
*		works for const Nyble types
*		returns the Nybles data
*	@params: none
*	@returns:
*		this->data : the calling Nyble's data
*/
unsigned char const Nyble::getNybleData() const
{
	return this->data;
}

/*	void setData(unsigned char new_data)
*		a mutator method for changing a Nybles private data type
*	@params:
		new_data : the unsigned char data we are seeing the calling Nyble's data to
	@returns: none
*/
void Nyble::setData(unsigned char new_data)
{
	this->data = new_data;
}

//---  End of File ---
