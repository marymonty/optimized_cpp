//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Mem.h"
#include "Heap.h"
#include "Type.h"

// To help with coalescing... not required
struct SecretPtr
{
	Free *pFree;
};


// ----------------------------------------------------
//  Initialized the Memory block:
//  Update the Heap
//  Create a free block
//  Heap structure links to free hdr
//-----------------------------------------------------
void Mem::initialize()
{
	// poHeap is the pointer to the heap
	Heap* pHeap = this->poHeap;
	assert(pHeap);
	// now we have our heap, pHeap, which points to the very top of the memory 

	// Get Start Location of Free Header
	// pHeap + 1 = pHeap plus the size of one pHeap, which gives us the end of the heap header
	// Heap* pHeapEnd = pHeap + 1; <- this is true, but we look at it also as the start of the free heap
	Free* pFreeStart = (Free*)(pHeap + 1);

	// Get The Size Of the initialized Free Block
	// find the bottom of the Free header
	// Free* pFreeEnd = pFree + 1 would work, but we can also look at the bottom of the free header
	// as the top of the free block
	uint32_t BlockStart = (uint32_t)(pFreeStart + 1);

	// TotalSize is 50K, if we do (pHeap + TotalSize) we have 50K pHeaps, not what we want
	// we want the bottom of the heap, which is at the location of TotalSize, the end of the Block
	// found by getting one mem byte and moving it down by TotalSize 
	uint32_t BlockEnd = ((uint32_t)pHeap + TotalSize);

	uint32_t BlockSize = BlockEnd - BlockStart;

	// Creat (Stamp) Free at Address
	// initialize the Free header
	Free* pFree = new(pFreeStart) Free(BlockSize);

	// update Heap information
	this->privSetFreeHead(pFree);
	this->privSetNextFit(pFree);
	this->privAddFreeBlock(BlockSize);
}


// ----------------------------------------------------
// Malloc
//  Find a free block that fits
//  Change it to used (may require subdivision)
//  Correct the heap Links (used,free) headers 
//  Update stats
//  Return pointer to block
//-----------------------------------------------------
void* Mem::malloc(const uint32_t _size)
{
	// find a free block
	assert(this->poHeap);
	// returnUsed is the Used pointer we will return (points to the start of the block, past the header)
	Used* returnUsed = nullptr;
	// we start the search for a free block to malloc at the start of pNextFit list, NOT pFreeHead
	Free* freeTraverser = this->poHeap->pNextFit;
	// the looping constraint is not nullptr, it's if we start at pNextFit and loop back to pNextFit
	// without finding any free block big enough
	bool fullLoop = false;
	if (freeTraverser)
	{
		while (fullLoop != true)
		{	// we have not fully looped through the pNextFit list
			if (freeTraverser->mAllocSize == _size)
			{	// we just move the whole Free block to be a Used block
				// check if there are other Free blocks that we need to re-order
				removeFreeBlock(freeTraverser);
				// took care of next and prev pointers for the free block, free to remove it
				Used* newUsedBlock = (Used*)freeTraverser;
				// update the data in the newUsedBlock
				updateNewUsed(newUsedBlock);
				// add the Used block to the pUsedHead list
				addUsedBlockToHead(newUsedBlock);
				// we want to return below the header, so we need to add 1 to the pointer
				returnUsed = (this->poHeap->pUsedHead + 1);
				// increment the current number of used blocks and the used memory size
				increaseUsed(_size);
				// decrement the number of free blocks and free memory size
				decreaseFree(_size);
				// get to the bottom of newUsed to make sure bAboveFree is false 
				setFalseBAboveFree(newUsedBlock);
				// break out of the loop since we successfully malloc'ed
				break;
			}

			else if (freeTraverser->mAllocSize > _size)
			{
				// store a pointer to the end of the full free block
				Free* endFreeBlock = (Free*)((uint32_t)freeTraverser + (uint32_t)freeTraverser->mAllocSize);
				// store the next and prev pointers of the free block
				Free* ogFreepNext = freeTraverser->pNext;
				Free* ogFreepPrev = freeTraverser->pPrev;
				// check if the free block is pointed to by pFreeHead
				bool isFreeHead = false;
				// set isFreeHead by checking if the original free block was pFreeHead
				checkIfFreeHead(freeTraverser, isFreeHead);
				// create the Used portion of the free block 
				Used* newUsed = (Used*)freeTraverser;
				newUsed = new(newUsed) Used(_size);
				// add the used block to the start of the heaps pUsedHead
				addUsedBlockToHead(newUsed);
				// add a Used Block to the count, increase memUsed size by size of the block, not block+header
				increaseUsed(_size);
				// we want to return below the header, so we need to add 1 to the pointer
				returnUsed = (this->poHeap->pUsedHead + 1);

				// find where the Used block ends by going past the header, store in freeStart pointer
				Free* freeStart = nullptr;
				findEndOfUsedBlock(newUsed, freeStart);
				// find the difference in sizes of Free pre-subdivision and Free post-subdivision
				// by subtracting the initial end of the Free block pointer minus the start of 
				// the subdivided Free block pointer (casting both pointers to char *s so that we
				// find the difference in bytes)
				uint32_t freeSizeDifference = (uint32_t)((char*)endFreeBlock - (char*)(freeStart));
				// find the full size of the Used block (since with the header it will be 
				// larger than _size
				uint32_t usedSizeDifference = (uint32_t)((char*)freeStart - (char*)(newUsed));
				// subract the size of the Used Block + the size of the Used Block's header
				this->poHeap->currFreeMem -= usedSizeDifference;
				// create the subdivided Free block
				Free* newerFree = new(freeStart) Free(freeSizeDifference);
				// update the newerFree data
				updateNewFree(newerFree, ogFreepPrev, ogFreepNext, isFreeHead);
				// set pNextFit to be the newerFree block, since we just inserted into it
				// it should be the next place we look to insert again
				this->poHeap->pNextFit = newerFree;
				// add a secret pointer to the end of this free block
				adjustSecretPointer(newerFree);
				// break out of the loop since we successfull malloc'ed
				break;
			}
			// this free block (freeTraverser) could not fit the desired malloc, so go to the next one
			freeTraverser = freeTraverser->pNext;
			// check if we have made a fullLoop through the pNextFitList
			checkpNextFitList(freeTraverser, fullLoop);
		}
	}
	return returnUsed;
}


// ----------------------------------------------------
//  Return the free block to the system
//  May require Coalescing
//  Correct the heap Links (used,free) headers 
//  Update stats
// 
// 2 THINGS we always need to do when we delete
//	1.	tell your below neighbor that you are now free
//			i.e. set their bAboveFree bool to True
//	2.	bury your secret
//			i.e. make a SecretPtr struct as you point to the block below you. 
//				The SecretPtr points to your start address so you can be accessed later. 
//-----------------------------------------------------
void Mem::free(void* const data)
{
	// the beginning address of the Used block is the header, which is at data-1
	Used* uRemoving = ((Used*)data - 1);

	// update the removing block pointers so it can be removed
	removeUsedBlock(uRemoving);

	// there is no while loop to check anything, we just 
	// turn the used block into a free block at the address its already at
	Free* newlyFree = (Free*)uRemoving;
	newlyFree->mType = Type::FREE_Type;

	// coalescing doesnt matter for this, decreaseUsed size and count
	decreaseUsed((uint32_t)newlyFree->mAllocSize);
	// find the size difference in the used block being freed
	uint32_t newlyFreeBlockStart = (uint32_t)(newlyFree + 1);
	uint32_t newlyFreeBlockEnd = (uint32_t)(newlyFreeBlockStart + (uint32_t)newlyFree->mAllocSize);
	uint32_t usedSizeDifference = (uint32_t)(newlyFreeBlockEnd - newlyFreeBlockStart);
	// increase the free mem and block counts
	increaseFree(usedSizeDifference);
	// bool values to keep track of coalesces and pFreeHead
	bool coalesceBelow = false;
	bool coalesceAbove = false;
	bool wasFreeHead = false;

	// check the block below the newly free block to see if it's also free
	// in which case we coalesce the two blocks within the function
	checkBelow(newlyFree, coalesceBelow, wasFreeHead);

	// check the block above the newly free block to see if it's also free
	// in which case we coalesce the two blocks 
	checkAbove(newlyFree, coalesceAbove, coalesceBelow, wasFreeHead);

	// set the block below the free block to have their bAboveFree flag set to true
	setBAboveFree(newlyFree);
	// adjust the secret pointer in this newly free block to point to its starting address
	adjustSecretPointer(newlyFree);

	// if there is nothing above or below, we have never reset pFreeHead and pNextFit
	if (coalesceBelow == false && coalesceAbove == false)
	{	// need to check to update pFreeHead and pNextFit
		readjustPFreeHead(newlyFree);
	}
}


/*	removeFreeBlock
*		for when we are fully removing a free block to move to used block
*		we need to change the pPrev and pNext pointers to remove the current block
*/
const void Mem::removeFreeBlock(Free* freeTraverser)
{
	assert(freeTraverser != nullptr);
	if (freeTraverser->pNext != nullptr)
	{	// there are free blocks connected after this free block
		freeTraverser->pNext->pPrev = freeTraverser->pPrev;
	}
	if (freeTraverser->pPrev != nullptr)
	{	// there are free blocks connected before this free block
		freeTraverser->pPrev->pNext = freeTraverser->pNext;
	}
	else
	{	// freeTraverser is pFreeHead, so set pFreeHead to pNext (might be nullptr)
		if (freeTraverser->pNext != nullptr)
		{
			this->poHeap->pFreeHead = freeTraverser->pNext;
			this->poHeap->pNextFit = freeTraverser->pNext;
		}
		else
		{
			this->poHeap->pFreeHead = nullptr;
			this->poHeap->pNextFit = nullptr;
		}
	}
}


/*	removeUsedBlock
*		adding the new Used block to the pUsedHead pointer
*		off of the heap, reordering any other pointers needed
*/
const void Mem::removeUsedBlock(Used* uRemoving)
{
	assert(uRemoving != nullptr);

	if (uRemoving->pNext != nullptr)
	{	// there is a Used block after this one
		uRemoving->pNext->pPrev = uRemoving->pPrev;
	}

	if (uRemoving->pPrev != nullptr)
	{	// there is a used block before this one
		uRemoving->pPrev->pNext = uRemoving->pNext;
	}
	else
	{	// there is nothing before this one, so update pUsedHead
		this->poHeap->pUsedHead = uRemoving->pNext;
	}
	uRemoving->pNext = nullptr;
	uRemoving->pPrev = nullptr;
}


/*	addUsedBlockToHead
*		pUsedHead has no ordering so we just push every new Used block to the front
*		of pUsedHead. This function sets pUsedHead to the new Used block - newUsed.
*/
const void Mem::addUsedBlockToHead(Used* newUsed)
{
	assert(newUsed);
	newUsed->pPrev = nullptr;
	if (this->poHeap->pUsedHead != nullptr)
	{	// there is already a head
		this->poHeap->pUsedHead->pPrev = newUsed;
		newUsed->pNext = this->poHeap->pUsedHead;
		this->poHeap->pUsedHead = newUsed;
	}
	else
	{	// there is no pUsedHead
		newUsed->pNext = nullptr;
		this->poHeap->pUsedHead = newUsed;
	}
}


/*	updateNewUsed
*		passed in a newly malloc-ed block
*		update the data in the newUsedBlock to set the type and the pointers
*/
const void Mem::updateNewUsed(Used*& newUsedBlock)
{
	assert(newUsedBlock);
	newUsedBlock->mType = Type::USED_Type;
	newUsedBlock->pNext = nullptr;
	newUsedBlock->pPrev = nullptr;
}


/*	updateNewFree
*		called when a used block is malloc'ed in a Free block with extra free space
*		the extra free space becomes a new Free block (newerFree)
*		we need to update the data of newerFree with the original Free blocks pointers (ogFreepPrev
*		and ogFreepNext), and with the info of if the original free block was pFreeHead
*/
const void Mem::updateNewFree(Free*& newerFree, Free*& ogFreepPrev, Free*& ogFreepNext, bool isFreeHead)
{
	assert(newerFree);
	// we cannot assert the ogFree pointers because they could be nullptr, and that's okay
	newerFree->mType = Type::FREE_Type;
	newerFree->pNext = ogFreepNext;
	if (ogFreepNext != nullptr)
	{	// the original pNext is part of the linked list, so update it
		ogFreepNext->pPrev = newerFree;
	}
	newerFree->pPrev = ogFreepPrev;
	if (ogFreepPrev != nullptr)
	{	// the original pPrev is part of the linked list, so update it
		ogFreepPrev->pNext = newerFree;
	}
	if (isFreeHead)
	{	// the original Free block was pFreeHead, so update pFreeHead with the new address
		this->poHeap->pFreeHead = newerFree;
	}
	// if newerFree was not the pFreeHead to begin with it should still be in place
	// by transfering the pNext and pPrev pointers
}


/*	increaseUsed
*		called when a new used block is created with the parameter _size
*		increase the count of currNumUsedBlocks by 1
*		increase the size of currUsedMem by _size
*/
const void Mem::increaseUsed(uint32_t _size)
{
	this->poHeap->currNumUsedBlocks += 1;
	this->poHeap->currUsedMem += _size;
}


/*	decreasedUsed
*		called when Freeing a used block
*		we are freeing one used block (even if we combine with other Free's)
*		and freeing the bytes in that Used->Free block
*/
const void Mem::decreaseUsed(uint32_t _size)
{
	this->poHeap->currNumUsedBlocks -= 1;
	this->poHeap->currUsedMem -= _size;
}


/*	decreaseFree
*		called when a new used block is created with parameter _size
*		decrease the number of currNumFreeBlocks by 1
*		decrease the size of currFreeMem by _size
*/
const void Mem::decreaseFree(uint32_t _size)
{
	this->poHeap->currFreeMem -= _size;
	this->poHeap->currNumFreeBlocks -= 1;
}


/*	increaseFree
*		called when a used block is being freed
*/
const void Mem::increaseFree(uint32_t _size)
{
	this->poHeap->currFreeMem += _size;
	this->poHeap->currNumFreeBlocks += 1;
}


/*	checkIfFreeHead
*		called when a block is malloc-ed but there is free space below it
*		OR called when coalescing
*		checks if the parameter freeTraverser (the block that is being malloc-ed)
*		was being pointed to by pFreeHead, if so, it sets isFreeHead to true
*/
const void Mem::checkIfFreeHead(Free* freeTraverser, bool &isFreeHead)
{
	assert(freeTraverser);
	if (this->poHeap->pFreeHead == freeTraverser)
	{
		isFreeHead = true;
	}
}

/*	checkIfNextFit
*		called when coalescing down
*		checks if the free block is the head of pNextFit
*		if so, set wasNextFit to be true
*/
const void Mem::checkIfNextFit(Free* pFreeEnd, bool& wasNextFit)
{
	assert(pFreeEnd);
	if (this->poHeap->pNextFit == pFreeEnd)
	{
		wasNextFit = true;
		this->poHeap->pNextFit = nullptr;
	}
}


/*	checkpNextFitList
*		this is called at the end of the while loop to see if we have made a full loop
*		through the pNextFit list, if we have, we set fullLoop to be true
*/
const void Mem::checkpNextFitList(Free*& freeTraverser, bool& fullLoop)
{
	// we don't need an assert statement since we are checking if freeTraverser is nullptr anyway
	if (freeTraverser == nullptr)
	{	// we reached the end of the list so go back to the beginning
		if (this->poHeap->pFreeHead != nullptr)
		{	// check that there is a beginning to go back to
			freeTraverser = this->poHeap->pFreeHead;
		}
		else
		{	// there are no free blocks in the list so we have completed an empty loop
			fullLoop = true;	// we should exit
		}
	}
	if (freeTraverser == this->poHeap->pNextFit)
	{	// we have made the full loop
		fullLoop = true;
	}
}


/*	findEndOfUsedBlock
*		called when we need to find and point to the end of the used block
*		uses a Free pointer to point to whatever is below the used block 
*/
const void Mem::findEndOfUsedBlock(Used* newUsed, Free* &freeStart)
{
	// go past the header of the used block
	uint32_t usedBlockStart = (uint32_t)(newUsed + 1);
	// then going to the end of the block since we know it is size _size
	uint32_t usedBlockEnd = (uint32_t)(usedBlockStart + newUsed->mAllocSize);

	// redefine the Free block below the Used block (at usedBlockEnd)
	freeStart = (Free*)(usedBlockEnd);
}


/*	findEndOfFreeBlock
*		called when we need to find and point to the end of the used block
*		uses a Free pointer to point to whatever is below the used block
*/
const void Mem::findEndOfFreeBlock(Free* newlyFree, Free* &pFreeEnd)
{
	// get to the end of the newly free block
	// find where the newlyFree block ends by going past the header
	uint32_t newlyFreeBlockStart = (uint32_t)(newlyFree + 1);
	// then going to the end of the block since we know its size from mAllocSize
	uint32_t newlyFreeBlockEnd = (uint32_t)(newlyFreeBlockStart + (uint32_t)newlyFree->mAllocSize);
	// pFreeEnd is the block below newlyFree (may or may not be free)
	pFreeEnd = (Free*)(newlyFreeBlockEnd);
}


/* checkBelow
*	function will check if the block under the freeing block is also a free block
*	in which case we coalesce the two blocks
*/
const void Mem::checkBelow(Free* &newlyFree, bool &coalesceBelow, bool &wasFreeHead)
{
	assert(newlyFree != nullptr);
	// get to the end of the newlyFree Block
	Free* pFreeEnd = nullptr;
	findEndOfFreeBlock(newlyFree, pFreeEnd);

	if (pFreeEnd != nullptr)
	{	// there is a block below this one
		if (pFreeEnd->mType == Type::FREE_Type)
		{	// below block is free, we need to coalesce
			// save the Free pointers
			Free* ogFreePNext = pFreeEnd->pNext;
			Free* ogFreePPrev = pFreeEnd->pPrev;
			// set the freeHead and nextFit bools
			checkIfFreeHead(pFreeEnd, wasFreeHead);
			bool wasNextFit = false;
			checkIfNextFit(pFreeEnd, wasNextFit);
			// save whether the newlyFree has bAboveFree = true
			bool setAboveFree = newlyFree->bAboveFree;

			// this block does not start under a header!!! it just starts, so no pFreeEnd + 1
			uint32_t underFreeBlockStart = (uint32_t)(pFreeEnd);
			// go to the end of the block since we know its size from mAllocSize
			uint32_t underFreeBlockEnd = (uint32_t)(underFreeBlockStart + (uint32_t)pFreeEnd->mAllocSize);
			Free* pBottomFreeEnd = (Free*)(underFreeBlockEnd);

			// find the difference in sizes of Free pre-subdivision and Free post-subdivision
			// by subtracting the initial end of the Free block pointer minus the start of 
			// the subdivided Free block pointer (casting both pointers to char *s so that we
			// find the difference in bytes
			uint32_t totalFreeSize = (uint32_t)((char*)pBottomFreeEnd - (char*)newlyFree);

			// totalFreeSize is the size of both free blocks atop one another combined
			// so we make a free block that is totalFreeSize and insert it at the address
			// of the top block
			// we will need to come back later to fix pointers, but we don't have to worry about that atm
			Free* combinedFree = new(newlyFree) Free(totalFreeSize);
			// update the pointers / data in combinedFree
			updateNewFree(combinedFree, ogFreePPrev, ogFreePNext, wasFreeHead);
			combinedFree->bAboveFree = setAboveFree;
			if (wasNextFit)
			{
				this->poHeap->pNextFit = combinedFree;
			}
			newlyFree = combinedFree;
			coalesceBelow = true;
			this->poHeap->currNumFreeBlocks -= 1;
			// need to add the size of a Free header to currFreeMem
			uint32_t endOfCombinedHeader = (uint32_t)(newlyFree + 1);
			uint32_t startOfCombinedHeader = (uint32_t)(newlyFree);
			this->poHeap->currFreeMem += (uint32_t)(endOfCombinedHeader-startOfCombinedHeader);
		}
	}
}


/*	checkAbove
*		function will check if the block above the freeing block is also a free block
*		in which case we coaslesce the two blocks
*/
const void Mem::checkAbove(Free* &newlyFree, bool &coalesceAbove, bool coalesceBelow, bool &wasFreeHead)
{
	assert(newlyFree != nullptr);
	if (newlyFree->bAboveFree == true)
	{	// the above block is free, so we need to coalesce
		// find the start of the free block by using its secret pointer
		SecretPtr* pSecret = (SecretPtr*)newlyFree;
		pSecret = pSecret - 1;
		Free* aboveFree = (Free*)pSecret->pFree;
		// save the above free blocks pointers
		Free* aboveFreePNext = aboveFree->pNext;
		Free* aboveFreePPrev = aboveFree->pPrev;
		// save the CURRENT (not above) blocks pNext pointer
		Free* newlyFreePNext = newlyFree->pNext;
		// check if the above block was the pFreeHead
		checkIfFreeHead(aboveFree, wasFreeHead);
		bool wasNextFit = false;
		// check if the block above was the pNextFit
		checkIfNextFit(aboveFree, wasNextFit);
		bool isNextFit = false;
		// check if the current block is the pNextFit
		checkIfNextFit(newlyFree, isNextFit);

		// getting the end of the newlyFree block
		Free* pFreeEnd = nullptr;
		findEndOfFreeBlock(newlyFree, pFreeEnd);

		// we have the start position (aboveFree) and the end position (pFreeEnd)
		uint32_t aboveFreeBlockStart = (uint32_t)(aboveFree + 1);
		uint32_t totalFreeBlockSize = (uint32_t)((uint32_t)pFreeEnd - (uint32_t)aboveFreeBlockStart);
		Free* combinedFree = new(aboveFree) Free(totalFreeBlockSize);
		// need to update pointers
		if (coalesceBelow == true) 
		{	// we already set the correct pNext when we coalesced the block below
			// so save this combinedFree's pNext to the current saved pNext pointer (newlyFreePNext)
			updateNewFree(combinedFree, aboveFreePPrev, newlyFreePNext, wasFreeHead);

		}
		else
		{	// we did not coalesce down, so we set pNext to the pNext of the above block
			updateNewFree(combinedFree, aboveFreePPrev, aboveFreePNext, wasFreeHead);
		}
		// update the pNextFit head if appropriate
		if (wasNextFit == true || isNextFit == true)
		{
			this->poHeap->pNextFit = combinedFree;
		}
		combinedFree->bAboveFree = false;
		newlyFree = combinedFree;
		coalesceAbove = true;

		// add the combined Free header back to currFreeMem
		uint32_t endOfCombinedHeader = (uint32_t)(newlyFree + 1);
		uint32_t startOfCombinedHeader = (uint32_t)(newlyFree);
		this->poHeap->currFreeMem += (uint32_t)(endOfCombinedHeader - startOfCombinedHeader);
		this->poHeap->currNumFreeBlocks -= 1;
	}
}


/*	readjustPFreeHead
*		called at the end of free() if the newly freed block was not coalesced above or below
*		this function readjusts pFreeHead if it was affected during the free
*/
const void Mem::readjustPFreeHead(Free* newlyFree)
{
	assert(newlyFree);
	if (this->poHeap->pNextFit == nullptr)
	{	// there is no pNextFit, so we set it to our free block
		this->poHeap->pNextFit = newlyFree;
	}
	if (this->poHeap->pFreeHead == nullptr)
	{	// there is no pFreeHead, so we set it to our free block
		this->poHeap->pFreeHead = newlyFree;
	}
	// the else's mean that newlyFree is explicity not the head
	// so we need to readjust pointers, find where newlyFree fits
	else if ((uint32_t)newlyFree < (uint32_t)this->poHeap->pFreeHead)
	{	// newlyFree is higher in the heap that the current pFreeHead so 
		// newlyFree should be pFreeHead
		this->poHeap->pFreeHead->pPrev = newlyFree;
		newlyFree->pNext = this->poHeap->pFreeHead;
		this->poHeap->pFreeHead = newlyFree;
		newlyFree->pPrev = nullptr;
	}
	else
	{	// newlyFree is not higher than the current pFreeHead so we need to find out
		// where exactly newlyFree fits in the pFreeHead list
		Free* freeHeadTraverser = this->poHeap->pFreeHead->pNext;
		while (freeHeadTraverser != nullptr)
		{	// go through all the Free blocks in the pFreeHead list
			if ((uint32_t)newlyFree < (uint32_t)freeHeadTraverser)
			{	// our newlyFree block is higher than the next block in the pFreeHead list
				// so this is where our newlyFree block fits - above this next block
				newlyFree->pPrev = freeHeadTraverser->pPrev;
				newlyFree->pPrev->pNext = newlyFree;
				newlyFree->pNext = freeHeadTraverser;
				freeHeadTraverser->pPrev = newlyFree;
				break;
			}
			freeHeadTraverser = freeHeadTraverser->pNext;
		}
	}
}

/*	setFalseBAboveFree
*		called when a new used block is created
*		go to the block below the new used block (if one exists)
*		and set their bAboveFree flag to be false since there is not a Free block above them
*/
const void Mem::setFalseBAboveFree(Used* newUsedBlock)
{
	assert(newUsedBlock);
	// get to the end of the newly malloc-ed used block
	Free* pFreeStart = nullptr;
	findEndOfUsedBlock(newUsedBlock, pFreeStart);
	// get to the end of the heap
	uint32_t pHeapEnd = (uint32_t)((uint32_t)this->poHeap + (this->poHeap->currUsedMem + this->poHeap->currFreeMem));
	// if the bottom of the used block is before the bottom of the heap
	if ((uint32_t)pFreeStart < pHeapEnd)
	{	// set whatever is below this used block's bAboveFree to be false
		Used* underBlock = (Used*)pFreeStart;
		underBlock->bAboveFree = false;
	}
}

/*	setBAboveFree
*		called when a new free block is created
*		go to the block below the new free block (if one exists)
*		and set their bAboveFree flag to be true since there is now a Free block above them
*/
const void Mem::setBAboveFree(Free* newlyFree)
{
	Free* pFreeEnd = nullptr;
	findEndOfFreeBlock(newlyFree, pFreeEnd);
	// might need to add in sizeof(used header) * currNumUsedBlocks + sizeof(free header) * currNumFreeBlocks
	uint32_t pHeapEnd = (uint32_t)((uint32_t)this->poHeap + (this->poHeap->currUsedMem + this->poHeap->currFreeMem));

	if ((uint32_t)pFreeEnd < pHeapEnd)
	{	// theres nothing below this newlyFreeBlock
		pFreeEnd->bAboveFree = true;
	}
}


/*	adjustSecretPointer
*		called when we either malloc a block and have a new Free underneath it that needs a secret pointer
*		OR when we free a block and need to add / update their secret pointer
*/
const void Mem::adjustSecretPointer(Free*& newlyFree)
{
	assert(newlyFree);
	Free* pFreeEnd = nullptr;
	findEndOfFreeBlock(newlyFree, pFreeEnd);
	// make a secret pointer and point to the address of uRemoving
	SecretPtr* pSecret = (SecretPtr*)pFreeEnd;
	// place the pointer at pSecret-1
	pSecret = pSecret - 1;
	// set pFree to be the starting address of uRemoving
	pSecret->pFree = newlyFree;
}


// private functions for memory initialization
void Mem::privSetFreeHead(Free* p) const
{
	assert(p);
	assert(this->poHeap);
	this->poHeap->pFreeHead = p;
}
void Mem::privSetNextFit(Free* p) const
{
	assert(p);
	assert(this->poHeap);
	this->poHeap->pNextFit = p;
}
void Mem::privAddFreeBlock(uint32_t BlockSize) const
{
	assert(this->poHeap);
	this->poHeap->currFreeMem += BlockSize;
	this->poHeap->currNumFreeBlocks += 1;
}

// --- End of File ---
