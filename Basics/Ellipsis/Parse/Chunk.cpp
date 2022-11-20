//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Chunk.h"

// Add code here... if desired

bool checkIfChunk(const char* inputParam)
{
	bool isEnum = false;
	if (strcmp(inputParam, "VERTS_TYPE") == 0)
	{
		isEnum = true;
	}
	if (strcmp(inputParam, "NORMS_TYPE") == 0)
	{
		isEnum = true;
	}
	if (strcmp(inputParam, "ANIM_TYPE") == 0)
	{
		isEnum = true;
	}
	if (strcmp(inputParam, "TEXTURE_TYPE") == 0)
	{
		isEnum = true;
	}
	if (strcmp(inputParam, "UV_TYPE") == 0)
	{
		isEnum = true;
	}
	return isEnum;
}


// ---  End of File ---------------

