//---------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#include "answerRegistry.h"

#define QuestionAnswer(x,y)  Answer::registerAnswer(1,x,(unsigned int)y)

struct Cat
{
	Cat()
	:c0( 0xC9 ), c1(0xCA), c2(0xCB)
	{}

	unsigned char c0;
	unsigned char c1;
	unsigned char c2;
};

struct Dog
{
	Dog()
	: d0(0xDDAA), d1(0xDDBB), d2(0xDDCC)
	{}

	unsigned short d0;
	unsigned short d1;
	unsigned short d2;
};

struct Bird
{
	Bird()
	: b0(0xBB000111), b1(0xBB000222), b2(0xBB000333)
	{}

	unsigned int b0;
	unsigned int b1;
	unsigned int b2;
};


/*	petStore = 24 bytes
*	___________________________________
*	| catC0  | catC1 | catC2 | pad0   |
*	___________________________________
*	| dogD0  | dogD0 | dogD1 | dogD1  |
*	___________________________________
*	| dogD2  | dogD2 | pad1  | pad2   |
*	___________________________________
*	| birdB0 | birdB0| birdB0| birdB0 |
*	___________________________________
*	| birdB1 | birdB1| birdB1| birdB1 |
*	___________________________________
*	| birdB2 | birdB2| birdB2| birdB2 |
*	___________________________________
* 
*/
struct petStore
{
	Cat		morris;	// 3 bytes
	char	pad0;	// 1 byte
	Dog		fido;	// 6 bytes
	char    pad1;	// 1 byte
	char    pad2;	// 1 byte
	Bird	poly;	// 12 bytes
};


void Students_Casting()
{
	petStore		ps;
	unsigned int	*r;
	unsigned short	*s;
	unsigned char	*p;

	p = &ps.morris.c0;	// p = c9
	r = &ps.poly.b0;	// r = bb000111
	s = &ps.fido.d0;	// s = ddaa

	// HERE's the rules
	// Only ps - the petStore is instantiated
	//
	// Everything is stubbed out... just fill in the questions
	// Add code to find the answer programmatically  (by writing code)

	//      question 0) what is the value of morris.c1?
	
	// example
	int val;
	val = p[1];		//ca
	QuestionAnswer( 0, val );

	//      question 1)  What is the value of r[0]
	//      question 2)  What is the value of r[1]
	//      question 3)  What is the value of r[2]
	unsigned int valR;
	valR = r[0];		//bb000111
	QuestionAnswer( 1, valR);
	valR = r[1];		//bb000222
	QuestionAnswer( 2, valR);
	valR = r[2];		//bb000333
	QuestionAnswer( 3, valR);

	//      question 4)  What is the value of s[0]
	//      question 5)  What is the value of s[1]
	//      question 6)  What is the value of s[2]
	unsigned short valS;
	valS = s[0];			//ddaa
	QuestionAnswer( 4, valS);
	valS = s[1];			//ddbb
	QuestionAnswer( 5, valS);
	valS = s[2];			//ddcc
	QuestionAnswer( 6, valS);

	//      question 7)  What is the value of  p[0]
	//      question 8)  What is the value of  p[1]
	//      question 9)  What is the value of  p[2]
	unsigned char valC;
	valC = p[0];			//c9
	QuestionAnswer( 7, valC);
	valC = p[1];			//ca
	QuestionAnswer( 8, valC);
	valC = p[2];			//cb
	QuestionAnswer( 9, valC);

// For the next set of questions (11-19)
//
// You can cast and create temp variables to help you answer questions correctly.
// 	   No need to ever loop... use casting
//   p <- the starting address of ps
//   s <- the starting address of ps
//   r <- the starting address of ps

	p = (unsigned char *)&ps;
	s = (unsigned short *)&ps;
	r = (unsigned int *)&ps;

	//      question 10)  addr of ps
	// the pointer is at its own address, we just need to cast it to read it
	// all pointers are pointing to the same starting address of ps
	unsigned int pAddress = (unsigned int)p;	
	QuestionAnswer(10, pAddress);


/*	petStore = 24 bytes
*	___________________________________
*	| catC0  | catC1 | catC2 | pad0   |
*	___________________________________
*	| dogD0  | dogD0 | dogD1 | dogD1  |
*	___________________________________
*	| dogD2  | dogD2 | pad1  | pad2   |
*	___________________________________
*	| birdB0 | birdB0| birdB0| birdB0 |
*	___________________________________
*	| birdB1 | birdB1| birdB1| birdB1 |
*	___________________________________
*	| birdB2 | birdB2| birdB2| birdB2 |
*	___________________________________
*
*/

	//      question 11)  number of unsigned chars to d0
	//      question 12)  number of unsigned chars to c1
	//      question 13)  number of unsigned chars to b2

	//subtraction - the difference between pointers is the distance in array elements
	//		between the two elements. If we convert everything to char *, then the 
	//		difference between pointers will be the amount of bytes between the two
	//		from there we can cast that number of bytes to the correct type

	// I pasted my image of the data layout above, I can use that to just count 
	// the number of bytes to get to the d0, c1, b2 etc I am looking for
	// also checked my numbers with Trace::out statements
	
	// 11 - unsigned chars to d0	(4)
	unsigned char numChars = (unsigned char)((unsigned char*)&ps.fido.d0 - (unsigned char*)s);
	QuestionAnswer(11, numChars);
	// 12 - unsigned chars to c1	(1)
	numChars = (unsigned char)((unsigned char*)&ps.morris.c1 - (unsigned char *)p);
	QuestionAnswer(12, numChars);
	// 13 - unsigned chars to b2	(20)
	numChars = (unsigned char)((unsigned char*)&ps.poly.b2 - (unsigned char *)r);
	QuestionAnswer(13, numChars);

	//      question 14)  number of unsigned shorts to the first d2
	//      question 15)  number of unsigned shorts to the first c2
	//      question 16)  number of unsigned shorts to the first b1;

	// I have a typeSize var for the next two sets of questions so I can still just
	// find the difference between the pointers in bytes, then I divide that number
	// by the typeSize (2 for short, 4 for int) to get the number of those types
	// between our start and end pointers
	unsigned int typeSize = 2;

	// 14 - unsigned short to d2	(4)
	unsigned int numBytes = (unsigned int)((unsigned char*)&ps.fido.d2 - (unsigned char *)s);
	numBytes = numBytes / typeSize;
	unsigned short numShorts = (unsigned short)numBytes;
	QuestionAnswer(14, numShorts);
	// 15 - unsigned shorts to c2	(1)
	numBytes = (unsigned int)((unsigned char*)&ps.morris.c2 - (unsigned char*)p);
	numBytes = numBytes / typeSize;
	numShorts = (unsigned short)numBytes;
	QuestionAnswer(15, numShorts);
	// 16 - unsigned shorts to b1	(8)
	numBytes = (unsigned int)((unsigned char*)&ps.poly.b1 - (unsigned char*)r);
	numBytes = numBytes / typeSize;
	numShorts = (unsigned short)numBytes;
	QuestionAnswer(16, numShorts);
	

	//      question 17)  number of unsigned ints to the first d0
	//      question 18)  number of unsigned ints to the first c0
	//      question 19)  number of unsigned ints to the first b0;

	typeSize = 4;

	// 17 - unsigned ints to d0		(1)
	numBytes = (unsigned int)((unsigned char*)&ps.fido.d0 - (unsigned char*)s);
	numBytes = numBytes / typeSize;
	QuestionAnswer(17, numBytes);
	// 18 - unsigned ints to c0		(0)
	numBytes = (unsigned int)((unsigned char*)&ps.morris.c0 - (unsigned char*)p);
	numBytes = numBytes / typeSize;
	QuestionAnswer(18, numBytes);
	// 19 - unsigned ints to b0		(3)
	numBytes = (unsigned int)((unsigned char*)&ps.poly.b0 - (unsigned char*)r);
	numBytes = numBytes / typeSize;
	QuestionAnswer(19, numBytes);

}

// --- End of File ---

