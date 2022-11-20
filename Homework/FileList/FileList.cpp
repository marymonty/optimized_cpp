//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "AList.h"
#include "Node.h"
#include "FileList.h"

#include "Framework.h"
// --------------------------------
// -->    MODIFY This FILE    <----
// --------------------------------

FileList::FileList()
: pHead(nullptr),
NumNodes(0)
{
	// Hint you might need to rework this...
	// if you add data to FileList class
}

FileList::~FileList()
{
	if (this->pHead != nullptr)
	{
		Node* memBlock = this->pHead;
		delete memBlock;
	}
	
}


void FileList::WriteToFile(const char * const pFileName, AList *pAList)
{
	// Make sure you close the file after you fill it
	// Use fopen,fwrite,ftell,...,fclose

	// Hint: Open the file, write the nodes into the file 

	// Grads - You need to do the Load-In-Place technique
	//         You cannot have more than 2 new functions in this method

	// Everyone - Fill in your CustomDestructCommand::Command() that will be used 
	//            in the destructor..


	FILE* pFileHandle = nullptr;
	// try to open the file and make sure it worked
	assert(pFileName);
	errno_t status;
	// wb is for writing to a binary file
	status = fopen_s(&pFileHandle, pFileName, "wb");
	assert(pFileHandle);
	assert(status == 0);

	size_t numBytesWritten = 0;
	Node* traverser = pAList->GetHead();
	//AList is a linked list of Nodes
	while (traverser != nullptr)
	{
		// NEED TO PASS THE POINTER ITSELF, NOT A REFERENCE!!!!!
		numBytesWritten += fwrite(traverser, 1, sizeof(Node), pFileHandle);
		traverser = traverser->pNext;
	}
	assert(numBytesWritten == (sizeof(Node) * pAList->GetNumNodes()));
	// close the file once written
	fclose(pFileHandle);

}

FileList::FileList(const char * const pFileName, int numNodes)
{
	// Create the Linked List... You cannot use the original code
	// The input file, and numNodes is all you need to recreate the FileList
	
	// Hint: Open the file, read and create new nodes, 
	//       fill them with the data from the file

	// Grads - You need to do the Load-In-Place technique
	//         You cannot have more than 2 new functions in this method

	// Everyone - Fill in your CustomDestructCommand::Command() that will be used 
	//            in the destructor.


	this->pHead = nullptr;
	this->NumNodes = 0;

	FILE *pFileHandle;

	errno_t status;
	assert(pFileName);
	status = fopen_s(&pFileHandle, pFileName, "rb");
	assert(pFileHandle);
	assert(status == 0);

	size_t blockSize = sizeof(Node) * numNodes;
	char* data = new char[blockSize];
	fread_s(data, blockSize, sizeof(Node), (size_t)numNodes, pFileHandle);
	
	
	// at this point, we have the list of Nodes stored successfully into data
	// however, their pointers need to be updated (they still point to the old 
	// Node locations in memory)
	// we update by going through the block of memory (data) using pointer math
	// and casting each location to be a Node, then updating the pointers
	
	// how to access the first node
	Node* firstNode = (Node*)data;
	firstNode->pPrev = nullptr;
	// set this->pHead to be this firstNode
	this->pHead = firstNode;
	this->NumNodes = numNodes;

	// now loop through using pointer math
	char* pTraverser = data;
	Node* nextNode = nullptr;
	while (firstNode->pNext != nullptr)
	{
		nextNode = (Node*)(pTraverser + sizeof(Node));
		firstNode->pNext = nextNode;
		nextNode->pPrev = firstNode;
		firstNode = firstNode->pNext;
		pTraverser += sizeof(Node);
	}

	//assert(numElementsRead == (size_t)numNodes);
	fclose(pFileHandle);
}

// ---  End of File ---
