//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// Add functions and includes as needed

#include "Chunk.h"

int main(int argc, char *argv[])
{
	// argc is number of params passed
	// argv is the actual container the args are in

	// returnVal is 0 if successful, -1 if unsuccessful
	int returnVal = -1;

	// parameter format:
	// parse <options>
	// where options could be:
	//	-t CHUNK_TYPE
	//	-n CHUNK_NAME
	// CHUNK_TYPE has to be a valid ChunkType
	// CHUNK_NAME has to be a string of max 19 chars
	// we need all 5 paramters to be valid

	// say the paramter was parse -t UV_TYPE -n player_1
	// argv[0] = parse
	// argv[1] = -t
	// argv[2] = UV_TYPE
	// argv[3] = -n
	// argv[4] = player_1

	// the first thing to check is if argc == 5
	if (argc == 5)
	{
		// creating a typeFlag variable
		// typeFlag = 0 for -t or -T
		// typeFlag = 1 for -n or -N
		// typeFlag = -1 for anything else (invalid)
		int typeFlag = -1;
		int i = 1;
		// loop through the params starting at index 1
		while (i < argc)
		{
			//Trace::out(" \t\targv[%i] = %s \n", i, argv[i]);
			// odd index should be the type flags
			if (i % 2 == 1)
			{
				// set the typeFlag int if valid, or make invalid if not
				if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-T") == 0)
				{
					typeFlag = 0;
				}
				else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-N") == 0)
				{
					typeFlag = 1;
				}
				else
				{
					typeFlag = -1;
					break;
				}
			}
			else
			{
				// even params should be either ChunkType or name
				// based on what typeFlag came prior
				if (typeFlag == 0)
				{
					if (checkIfChunk(argv[i]) == true)
					{
						returnVal = 0;
					}
					else
					{
						returnVal = -1;
						break;
					}
				}
				else if (typeFlag == 1)
				{
					if (strlen(argv[i]) <= 19)
					{
						returnVal = 0;
					}
					else
					{
						returnVal = -1;
						break;
					}
				}
				// no matter what typeFlag came before, reset typeFlag to be -1
				typeFlag = -1;
			}
			i++;
		}
	}
	return returnVal;
}

// ---  End of File ---------------
