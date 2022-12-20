//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef MEM_H
#define MEM_H

#include "Heap.h"

class Mem
{
public:
	static const uint32_t TotalSize = (50 * 1024);
	static const uint32_t HeapAlign = 16;
	static const uint32_t HeapAlignMask = HeapAlign - 1;
	static const uint32_t HeaderGuards = 128;

	enum class Guard
	{
		Type_A,
		Type_5,
		Type_None
	};

public:

	Mem( Guard type );	

	Mem() = default;
	Mem(const Mem &) = delete;
	Mem & operator = (const Mem &) = delete;
	~Mem();

	// implement these functions
	void free( void * const data );
	void *malloc( const uint32_t size );
	void initialize( );

	// helper functions
	Heap *GetHeap();
	void Print(int count);

	/* MY HELPER FUNCTIONS */
	const void removeFreeBlock(Free* traverser);
	const void removeUsedBlock(Used* uRemoving);
	const void addUsedBlockToHead(Used* Utraverser);
	const void updateNewUsed(Used* &newUsedBlock);
	const void updateNewFree(Free*& newerFree, Free*& ogFreepPrev, Free*& ogFreepNext, bool isFreeHead);
	const void increaseUsed(uint32_t _size);
	const void decreaseUsed(uint32_t _size);
	const void decreaseFree(uint32_t _size);
	const void increaseFree(uint32_t _size);
	const void checkIfFreeHead(Free* freeTraverser, bool &isFreeHead);
	const void checkIfNextFit(Free* pFreeEnd, bool &wasNextFit);
	const void checkpNextFitList(Free*& freeTraverser, bool& fullLoop);
	const void findEndOfUsedBlock(Used* newUsed, Free* &freeStart);
	const void findEndOfFreeBlock(Free* newlyFree, Free*& pFreeEnd);
	const void checkBelow(Free* &newlyFree, bool &coalesceBelow, bool &wasFreeHead);
	const void checkAbove(Free* &newlyFree, bool &coalesceAbove, bool coalesceBelow, bool &wasFreeHead);
	const void readjustPFreeHead(Free* newlyFree);
	const void setFalseBAboveFree(Used* newUsedBlock);
	const void setBAboveFree(Free* newlyFree);
	const void adjustSecretPointer(Free* &newlyFree);
	/* END OF MY HELPER FUNCTIONS */

private:
	void privSetFreeHead(Free* p) const;
	void privSetNextFit(Free* p) const;
	void privAddFreeBlock(uint32_t BlockSize) const;

private:
	// Useful in malloc and free
	Heap *poHeap;

	// Below: 
	//    Not used in malloc, free, or initialize
	Guard type;	
	void *poRawMem;
};

#endif 

// --- End of File ---

