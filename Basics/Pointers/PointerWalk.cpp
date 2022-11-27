//---------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#include "answerRegistry.h"

#define QuestionAnswer(x,y)  Answer::registerAnswer(0,x,y)

unsigned char data[] =
{ 
  0xEB, 0xCD, 0x22, 0x4F,
  0x73, 0xB5, 0xF3, 0x35,
  0x23, 0x24, 0x01, 0xFE,
  0xCD, 0xE3, 0x44, 0x85,
  0x66, 0x43, 0x75, 0x33,
  0x39, 0x5C, 0x22, 0x11,
  0x56, 0xA8, 0xAA, 0x13,
  0x64, 0x82, 0x68, 0x26 
};


void Students_PointerWalk()
{
	//
	// STARTING:
	//
	//    unsigned char  *p;  // char are 8-bits long
	//    p = &data[0];       
	//
	// Q0:
	//    what value is p[0]?
	// Q1:
	//    what value is *(p+3)?
	// Q2:
	//    what value is *(2+p)?

    // ADD CODE to find the answer...
    // YES - you are coding here:

	/* MY CODE BELOW AND MY ANSWERS ARE INLINE COMMENTS */
	
	// example: 
	unsigned char *p;
	p = &data[0];
	unsigned char val = p[0];	//235  (0xeb)
	QuestionAnswer( 0, val);

	val = *(p+3);	//79  (0x4f)
	QuestionAnswer( 1, val);

	val = *(2 + p);	//34  (0x22)
	QuestionAnswer( 2, val);

	// Continuing (leaving the pointer where it is)
	//
	// 	 p = p + 12;
	//
	// Q3:
	//   what is value *(p)?
	// Q4:
	//   what is value p[3]?
	// Q5:
	//   what is value *p++?
	p = p + 12;
	val = *(p);		//205  (0xcd) 
	QuestionAnswer(3, val);
	val = p[3];		//133  (0x85) 
	QuestionAnswer(4, val);
	val = *p++;		//205  (0xcd) - the pointer is dereferenced BEFORE incrementing
	QuestionAnswer(5, val);

	// Continuing (leaving the pointer where it is)
	//
	//   p += 6;
	//
	// Q6:
	//   what is value *--p?
	// Q7:
	//   what is value p[3]?

	// remember, p was incremented after being dereferenced in the above val
	// so p starts at p+1 (or 227 or 0xe3)
	p += 6;		// this is at 51  (33)
	// I know parenthesis dont do anything, but it looks more readable
	val = *(--p);		//117  (0x75) - decrement first, then dereference
	QuestionAnswer(6, val);
	// remember, we decremented p in the last step, so p is 117 (0x75) NOT 51 (0x33)
	val = p[3];			//92  (0x5c)
	QuestionAnswer(7, val);

	// Continuing (leaving the pointer where it is)
	//
	//   p = p + 1;
	//
	// Q8:
	//   what is value *p++?
	// Q9:
	//   what is value *(p + 3)?
	p = p + 1;			//51  (0x33)
	val = *p++;			//51  (0x33) - dereference THEN increment
	QuestionAnswer(8, val);
	// remember p was incremented last step so p = 57 (0x39)
	val = *(p + 3);		//17  (0x11)
	QuestionAnswer(9, val);

	// Continuing (leaving the pointer where it is)
	//
	//	 p = 5 + p;
	//
	// Q10:
	//   what is value *(p++)?
	// Q11:
	//   what is value *(--p)?
	p = 5 + p;			//168 (0xa8)
	val = *(p++);		//168 (0xa8) - dereference THEN increment
	QuestionAnswer(10, val);
	// remember, p was incremented in last step
	val = *(--p);		//168 (0xa8) - decrement THEN dereference
	QuestionAnswer(11, val);
	// p still is at 168 (0xa8)

	//
	// STARTING:
	//
	//   unsigned int   *r;  // ints are 32-bits long
	//   r = (unsigned int *)&data[0];
	//
	// Q12:
	//   what is value *(r)?
	// Q13:
	//   what is value *(r + 3)?
	unsigned int* r;	// 4 bytes (32 bits)
	r = (unsigned int*)&data[0];	//referencing the data at data[0] and casting to an unsigned int pointer
	unsigned int val2;
	val2 = *(r);		//4f22cdeb	remember, the value is backwards!
	QuestionAnswer(12, val2);
	val2 = *(r + 3);	//8544e3cd
	QuestionAnswer(13, val2);


	// Continuing (leaving the pointer where it is)
	//
	//   r++;
	//
	// Q14:
	//   what is value *r++?
	//
	//	 r = r + 2;
	//
	// Q15:
	//   what is value r[1]?
	//
	//	 r = r + 1;
	//
	// Q16:
	//   what is value r[0]?
	r++;			// r is now 35f3b573
	val2 = *r++;	// 35f3b573 - dereferenced FIRST, then incremented
	QuestionAnswer(14, val2);
	// remember, r was incremented in the last step, so r = fe012423
	r = r + 2;		// r = 33754366
	val2 = r[1];	//11225c39
	QuestionAnswer(15, val2);
	r = r + 1;		// r = 11225c39
	val2 = r[0];	// 11225c39
	QuestionAnswer(16, val2);

	// Continuing (leaving the pointer where it is)
	// 
	// 	unsigned short *s;  // shorts are 16-bits long
	//	s = (unsigned short *)r;
	//
	// Q17:
	//   what is value s[-3]?
	//
	// s = s - 3;
	//
	// Q18:
	//   what is value s[2]?
	//
	// s += 5;
	//
	// Q19:
	//   what is value *(s + 3)?
	// Q20:
	//   what is value *(s)?

	// unsigned short is still written backwards
	// r = 11225c39 at this point
	unsigned short* s;	//2 bytes (16 bits)
	s = (unsigned short*)r;		// s = 5c39
	unsigned short val3;
	val3 = s[-3];		//8544
	QuestionAnswer(17, val3);
	s = s - 3;		// s = 8544
	val3 = s[2];	//3375
	QuestionAnswer(18, val3);
	s += 5;				// s = a856
	val3 = *(s + 3);	//2668
	QuestionAnswer(19, val3);
	val3 = *(s);		//a856
	QuestionAnswer(20, val3);

	// Continuing (leaving the pointer where it is)
	//
	//   p = (unsigned char *)s;
	//
	// Q21:
	//   what is value *(p + 1)?
	//
	//	 p += 5;
	//
	// Q22:
	//   what is value p[-9]?
	//
	//   --p;
	//
	// Q23:
	//   what is value p[0]?
	p = (unsigned char*)s;		// s = a856, so p = 56
	val = *(p + 1);				// a8
	QuestionAnswer(21, val);
	p += 5;					// p = 82
	val = p[-9];			// 39
	QuestionAnswer(22, val);
	--p;					// decrement p, p = 64
	val = p[0];				// 64
	QuestionAnswer(23, val);

}

// --- End of File ---

