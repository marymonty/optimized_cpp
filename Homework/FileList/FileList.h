//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef FileList_H
#define FileList_H

#include "Node.h"

class AList;

class FileList
{
public:
	// Big four
	FileList();
	~FileList();
	FileList(const FileList &) = delete;
	FileList &operator = (const FileList &) = delete;

	FileList(AList *p);

	// Accessors
	Node *GetHead() const;
	void SetHead(Node *pNode);
	int GetNumNodes();

	bool FindKey(unsigned int key, Node &foundNode);

	//---------------------------------------------------------------------------------------
	// Please implement(rework) these methods
	//---------------------------------------------------------------------------------------

	FileList(const char *const pFileName, int numNodes);
	void WriteToFile(const char *const pFileName, AList *pAList);

private:
	Node *pHead;
	int  NumNodes;

};

#endif 

// ---  End of File ---
