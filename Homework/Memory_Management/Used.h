//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef USED_H
#define USED_H

#include "Type.h"

class Free;

class Used
{
public:
   // ---------------------------------------------------------
   // Do not reorder, change or add data fields
   //     --> any changes to the data... 0 given to the assignment
   // You can add methods if you wish
   // ---------------------------------------------------------

    uint16_t   mAllocSize;    // size (16 bit)
    Type       mType;         // Type type 
    bool       bAboveFree;    // Type above is free (T/F)
    Used       *pNext;        // next free Type
    Used       *pPrev;        // prev free Type  

    Used() = default;

    Used(uint32_t blockSize);
};

#endif 

// --- End of File ---

