//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Used.h"
#include "Free.h"
#include "Type.h"

Free::Free(uint32_t blockSize)
	: mAllocSize((uint16_t)blockSize),
	mType(Type::FREE_Type),
	bAboveFree(false),
	pNext(nullptr),
	pPrev(nullptr)
{

}

Free::Free(Free* p)
	: mType(Type::FREE_Type)
{
	this->mAllocSize = p->mAllocSize;
	this->bAboveFree = p->bAboveFree;
	this->pNext = p->pNext;
	this->pPrev = p->pPrev;
}

Free::Free(Free* p, uint32_t usedSize)
	: mType(Type::FREE_Type)
{
	uint16_t usedSize16 = (uint16_t)usedSize;
	this->mAllocSize = (uint16_t)(p->mAllocSize - usedSize16);
	this->bAboveFree = p->bAboveFree;
	this->pNext = p->pNext;
	this->pPrev = p->pPrev;
}

// ---  End of File ---
