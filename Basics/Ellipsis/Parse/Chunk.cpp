//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Chunk.h"

// Add code here... if desired

/* MY CODE */
/* checkIfChunk
 * 	function to verify if the input parameter (inputParam)
 *	is one of the enum ChunkTypes
*/
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

/* END OF MY CODE */

// ---  End of File ---------------

