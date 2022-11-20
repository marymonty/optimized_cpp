//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef CHUNK_H
#define CHUNK_H

enum ChunkType
{
	VERTS_TYPE,
	NORMS_TYPE,
	ANIM_TYPE,
	TEXTURE_TYPE,
	UV_TYPE
};

bool checkIfChunk(const char* inputParam);
// Add functions protos

#endif 

// ---  End of File ---------------
