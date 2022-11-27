//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef NYBLE_H
#define NYBLE_H

//----------------------------------------------------------------------------
// Feel free to add extra methods in the class
// You need to explicitly define and implement the Big four operators
// Do not add extra data in class
// Do not add code here (that goes in *.cpp)
//----------------------------------------------------------------------------

class Nyble
{
public:
	
	/* my code */
	// Big Four operators - Default, Copy, Assignment, Destructor
	/*	Default Constructor	*/
	Nyble();
	/*	Specialized Constructor(s)	*/
	Nyble(const unsigned char c);
	Nyble(const unsigned int i);
	Nyble(const int i);
	/*	Copy Constructor	*/
	Nyble(const Nyble& r);
	/*	Assignment Operator	*/
	Nyble& operator = (const Nyble& r);
	/*	Destructor	*/
	~Nyble();

	/*	Nyble + constant	*/
	Nyble operator + (const int& c);
	/*	constant + Nyble	
		this is an external function, so you need friend	*/
	friend Nyble operator + (const int& r, const Nyble& s);
	/*	Nyble + Nyble	*/
	Nyble operator + (const Nyble& r);
	/*	Nyble += Nyble	*/
	Nyble operator += (const Nyble& r);

	/*	casting operator to unsigned int */
	operator unsigned int();

	/* end of my code */

	unsigned char getData();
	//my getData - accessible with const Nybles
	unsigned char const getNybleData() const;
	//my setData - accessible with const Nybles
	void setData(unsigned char new_data);

private:
        // Do not change this data
	unsigned char data;

};

/* my code */

/*	Unary Operators 
*		these are free functions of global scope, so defined outside the class	*/

/*	pre-increment 
*		++Nyble			*/
Nyble& operator++(Nyble& r);
/*	post-increment
*		Nyble++
*		we need the unused int in the declaration even though we dont use it	*/
Nyble operator++(Nyble& r, int unused); 
/*	our rotational bit shift function
*		Nyble << 1		*/
Nyble operator<<(const Nyble& r, const int times_shifted);
/*	ones compliment (bitwise NOT)
*		~Nyble			*/
Nyble operator~(const Nyble& r); // Bitwise complement
/*	addition of +3
*		+Nyble			*/
Nyble operator+(Nyble& r); // Assign sum

/* end of my code */

#endif

//---  End of File ---
