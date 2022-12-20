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
}


/* MY CODE */

FileList::~FileList()
{
	if (this->pHead != nullptr)
	{
		Node* memBlock = this->pHead;
		delete memBlock;
	}
}

/* WriteToFile
	open a binary file and write all nodes to the file
*/
void FileList::WriteToFile(const char * const pFileName, AList *pAList)
{
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

/* FileList
	creates the Linked List
	open the File, read and create new nodes using Load-in-Place (only one New)
	then fill the nodes with the data from the binary file
*/
FileList::FileList(const char * const pFileName, int numNodes)
{
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

/* END OF MY CODE */

// ---  End of File ---
