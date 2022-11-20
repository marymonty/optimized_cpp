//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Boustrophedonic.h"

/*	
*		GENERAL NOTES
*
* COORDINATES ARE (ROW, COL)
*	ROW	COL	COL	COL
*	ROW
*	ROW
* 
*
* if row is even (0, 2, etc), the nodes move pEast
* if row is odd (1, 3, etc), the nodes move pWest
* if row and col are both even OR both odd, pNorth and pSouth pointers 
	are pointing INTO node (if there is a node above and below that node)
* if row and col are even and odd or odd and even, pNorth and pSouth 
	pointers are pointing OUT of the node (if there are above / below nodes)
*/


void Remove(Node *&pHead, int row, int col)
{
	// first, find out if the row and col are even
	bool rowIsEven, colIsEven = false;
	checkEven(row, col, rowIsEven, colIsEven);

	// create a traverser node that will find the node to be deleted
	Node* traverser = pHead;

	// find the closest even row to the given row
	int closestEvenRow = 0;
	findClosestEvenRow(row, closestEvenRow);

	// move to the closestEvenRow
	moveToClosestEvenRow(traverser, closestEvenRow);
	
	// since we are in the closest even row, we go east to the col number 
	moveToCol(traverser, col);
	
	// then check if we are in the correct row or if we are in the row above
	if (closestEvenRow == row)
	{
		// we are at the node
		// take a lap around the node to fix pointers
		updatePointers(traverser, row, col);
	}
	else
	{
		// we are above the correct node
		// so move to the next row
		moveToNextRow(colIsEven, traverser);
		// then take a lap around the node and update the surrounding pointers
		updatePointers(traverser, row, col);
	}

	// all pointers should be fixed at this point, so we can delete the node
	deleteNode(traverser, pHead);
}


/*	checkEven
*		takes in the row and col and bools for whether the row and col are even
*			checks if the row and col are even 	
*			sets the rowIsEven and colIsEven params if either are true
*/
void checkEven(int row, int col, bool& rowIsEven, bool& colIsEven)
{
	if (row % 2 == 0)
	{
		rowIsEven = true;
	}
	if (col % 2 == 0)
	{
		colIsEven = true;
	}
}


/*	findClosestEvenRow
*		takes in the row and a zeroed int closestEvenRow
*		my method of removing starts with this function, findClosestEvenRow
*		we first get to the closest even row to the given row 
*		so we can just move straight east to the correct column
*			we find the closestEvenRow using integer math (row / 2)*2 
*			so example: we are deleting (7,5), 
*			our closest even row is (7/2) = 3, 3*2 = 6
*/
void findClosestEvenRow(int row, int& closestEvenRow)
{
	closestEvenRow = row / 2;
	closestEvenRow *= 2;
}


/*	moveToClosestEvenRow
*		move in a east, south, west, south pattern to move south through
*		the nodes to move through the rows as quickly as possible
*		stop at closestEvenRow
*/
void moveToClosestEvenRow(Node*& traverser, int closestEvenRow)
{
	int currentRow = 0;
	while (currentRow != closestEvenRow)
	{
		// if currentRow is even we need to move east, south, west
		if (currentRow % 2 == 0)
		{
			if (traverser->pEast != nullptr)
			{
				traverser = traverser->pEast;
				if (traverser->pSouth != nullptr)
				{
					traverser = traverser->pSouth;
					if (traverser->pWest != nullptr)
					{
						traverser = traverser->pWest;
						// we are now in the 0th col in the next row
					}
				}
			}
		}
		// if currentRow is odd we just need to move south
		else
		{
			if (traverser->pSouth != nullptr)
			{
				traverser = traverser->pSouth;
				// we are now in the 0th col in the next row
			}
		}
		currentRow++;
	}
}


/*	moveToCol
*		move east across the col in the closestEvenRow
*		to get to the col we are deleting
*/
void moveToCol(Node*& traverser, int col)
{
	int currentCol = 0;
	while (currentCol != col)
	{
		// we just need to move east
		if (traverser->pEast != nullptr)
		{
			traverser = traverser->pEast;
		}
		currentCol++;
	}
}


/*	moveToNextRow
*		we are above the node that needs to be deleted
*		so depending on if the col is odd or even, we need to move
*		south one row to get to the node we are deleting
*/
void moveToNextRow(bool colIsEven, Node*& traverser)
{
	// if col is even, we move one more east, then south, then west
	if (colIsEven == true)
	{
		if (traverser->pEast != nullptr)
		{
			traverser = traverser->pEast;
			if (traverser->pSouth != nullptr)
			{
				traverser = traverser->pSouth;
				if (traverser->pWest != nullptr)
				{
					traverser = traverser->pWest;
					// we are now at the correct node to delete
				}
			}
		}
	}
	// if col is odd, we just move south
	else
	{
		if (traverser->pSouth != nullptr)
		{
			traverser = traverser->pSouth;
			// we are now at the correct node to delete
		}
	}

}


/*	updatePointers
*		take all of the possible loops around the node being deleted
*		store pointers to the nodes north, east, south, and west of the deleting node
*		update those node's pointers to account for the removal of the deleting node
*/
void updatePointers(Node*& deletingNode, int row, int col)
{
	assert(deletingNode != nullptr);
	// store if the row and col are even
	bool rowIsEven, colIsEven = false;
	checkEven(row, col, rowIsEven, colIsEven);

	// create a traverser node that points to the node we are deleting
	Node* traverser = deletingNode;
	// nodeDirection will be set to the node in that direction of the deleting node
	// NOT where deleting node is pointing, but the node itself in the 
	// north/east/south/west direction
	Node* nodeNorth = nullptr;
	Node* nodeEast = nullptr;
	Node* nodeSouth = nullptr;
	Node* nodeWest = nullptr;

	// we check every possible route depending on if the row / col are even / odd
	if (rowIsEven == true)
	{
		if (colIsEven == true)
		{
			evenRowEvenColLoops(traverser, nodeNorth, nodeEast, nodeSouth, nodeWest, deletingNode);
		}
		else
		{
			evenRowOddColLoops(traverser, nodeNorth, nodeEast, nodeSouth, nodeWest, deletingNode);
		}
	}
	else
	{
		// row is odd
		if (colIsEven == true)
		{
			oddRowEvenColLoops(traverser, nodeNorth, nodeEast, nodeSouth, nodeWest, deletingNode);
		}
		else
		{
			// col is odd
			oddRowOddColLoops(traverser, nodeNorth, nodeEast, nodeSouth, nodeWest, deletingNode);
		}
	}

	// if they exist, we should at this point have
	// nodeNorth, nodeEast, nodeSouth, and nodeWest
	// we need to update their pointers before deleting our deletingNode
	updateBoarderNodes(nodeNorth, nodeEast, nodeSouth, nodeWest);
}



/*	evenRowEvenColLoops
*		we are going through the four possible loops to find nodes in all directions
*		of the node we are deleting
* if we are in an even row, we are moving east
* if we are in an even column, we need nodes in all directions
*				node
*				 v
*		node >  node  >  node
*				 ^
*				node
* the loops we could take are:
*	east, south, west, north	
*	east, north, west, south	
*	east, south, west, west, west, north, east, east 
*	east, north, west, west, west, south, east, east 
*/
void evenRowEvenColLoops(Node*& traverser, Node*& nodeNorth, Node*& nodeEast, 
						Node*& nodeSouth, Node*& nodeWest, Node* deletingNode)
{
	// loop 1 : east, south, west, north	
	if (traverser->pEast != nullptr)
	{
		traverser = traverser->pEast;
		// at the node directly east of the node we are deleting
		nodeEast = traverser;
		if (traverser->pSouth != nullptr)
		{
			traverser = traverser->pSouth;
			if (traverser->pWest != nullptr)
			{
				traverser = traverser->pWest;
				// traverser is at the node south of our deleting node
				nodeSouth = traverser;
			}
		}
	}
	// traverser may be set to elsewhere in the chain, so reset traverser
	traverser = deletingNode;
	
	// loop 2 : east, north, west, south	
	if (traverser->pEast != nullptr)
	{
		traverser = traverser->pEast;
		// at the node directly east of the node we are deleting
		nodeEast = traverser;
		if (traverser->pNorth != nullptr)
		{
			traverser = traverser->pNorth;
			if (traverser->pWest != nullptr)
			{
				traverser = traverser->pWest;
				// traverser is at the node north of our deleting node
				nodeNorth = traverser;
			}
		}
	}
	// traverser may be set to elsewhere in the chain, so reset traverser
	traverser = deletingNode;

	// loop 3 : east, south, west, west, west, north, east, east 
	if (traverser->pEast != nullptr)
	{
		traverser = traverser->pEast;
		// at the node directly east of the node we are deleting
		nodeEast = traverser;
		if (traverser->pSouth != nullptr)
		{
			traverser = traverser->pSouth;
			if (traverser->pWest != nullptr)
			{
				traverser = traverser->pWest;
				// traverser is at the node south of our deleting node
				nodeSouth = traverser;
				// keep going west
				if (traverser->pWest != nullptr)
				{
					traverser = traverser->pWest;
					if (traverser->pWest != nullptr)
					{
						traverser = traverser->pWest;
						if (traverser->pNorth != nullptr)
						{
							traverser = traverser->pNorth;
							if (traverser->pEast != nullptr)
							{
								traverser = traverser->pEast;
								// we are at the node west of the deleteing node
								nodeWest = traverser;
							}
						}
					}
				}
			}
		}
	}
	// traverser may be set to elsewhere in the chain, so reset traverser
	traverser = deletingNode;

	// loop 4 : east, north, west, west, west, south, east, east 
	if (traverser->pEast != nullptr)
	{
		traverser = traverser->pEast;
		// at the node directly east of the node we are deleting
		nodeEast = traverser;
		if (traverser->pNorth != nullptr)
		{
			traverser = traverser->pNorth;
			if (traverser->pWest != nullptr)
			{
				traverser = traverser->pWest;
				// traverser is at the node north of our deleting node
				nodeNorth = traverser;
				// keep going west
				if (traverser->pWest != nullptr)
				{
					traverser = traverser->pWest;
					if (traverser->pWest != nullptr)
					{
						traverser = traverser->pWest;
						if (traverser->pSouth != nullptr)
						{
							traverser = traverser->pSouth;
							if (traverser->pEast != nullptr)
							{
								traverser = traverser->pEast;
								// we are at the node west of the deleteing node
								nodeWest = traverser;
							}
						}
					}
				}
			}
		}
	}
}


/*	evenRowOddColLoops
*		we are going through the four possible loops to find nodes in all directions
*		of the node we are deleting
* if we are in an even row, we are moving east
* if we are in an odd column, we only need the east and west nodes
*				node
*				 ^
*		node >  node  >  node
*				 v
*				node
* the loops we could take are:
*	south, west, north, east
*	north, west, south, east
*	east, east, north, west, west, west, south, east
*	east, east, south, west, west, west, north, east
*/
void evenRowOddColLoops(Node*& traverser, Node*& nodeNorth, Node*& nodeEast, 
						Node*& nodeSouth, Node*& nodeWest, Node* deletingNode)
{
	// loop 1 : south, west, north, east
	if (traverser->pSouth != nullptr)
	{
		traverser = traverser->pSouth;
		// we are at the node south of the deleting node
		nodeSouth = traverser;
		if (traverser->pWest != nullptr)
		{
			traverser = traverser->pWest;
			if (traverser->pNorth != nullptr)
			{
				traverser = traverser->pNorth;
				// we are at the node west of the deleting node
				nodeWest = traverser;
			}
		}
	}
	// traverser may be set to elsewhere in the chain, so reset traverser
	traverser = deletingNode;

	// loop 2 : north, west, south, east
	if (traverser->pNorth != nullptr)
	{
		traverser = traverser->pNorth;
		// we are at the node north of the deleting node
		nodeNorth = traverser;
		if (traverser->pWest != nullptr)
		{
			traverser = traverser->pWest;
			if (traverser->pSouth != nullptr)
			{
				traverser = traverser->pSouth;
				// we are at the node west of the deleting node
				nodeWest = traverser;
			}
		}
	}
	// traverser may be set to elsewhere in the chain, so reset traverser
	traverser = deletingNode;

	// loop 3 : east, east, north, west, west, west, south, east
	if (traverser->pEast != nullptr)
	{
		traverser = traverser->pEast;
		// we are at the node east of the deleting node
		nodeEast = traverser;
		if (traverser->pEast != nullptr)
		{
			traverser = traverser->pEast;
			if (traverser->pNorth != nullptr)
			{
				traverser = traverser->pNorth;
				if (traverser->pWest != nullptr)
				{
					traverser = traverser->pWest;
					if (traverser->pWest != nullptr)
					{
						traverser = traverser->pWest;
						// we are at the node directly north of the deleting node
						nodeNorth = traverser;
						if (traverser->pWest != nullptr)
						{
							traverser = traverser->pWest;
							if (traverser->pSouth != nullptr)
							{
								traverser = traverser->pSouth;
								// we are at the node directly west of the deleting node
								nodeWest = traverser;
							}
						}
					}
				}
			}
		}
	}
	// traverser may be set to elsewhere in the chain, so reset traverser
	traverser = deletingNode;

	// loop 4 : east, east, south, west, west, west, north, east
	if (traverser->pEast != nullptr)
	{
		traverser = traverser->pEast;
		// we are at the node east of the deleting node
		nodeEast = traverser;
		if (traverser->pEast != nullptr)
		{
			traverser = traverser->pEast;
			if (traverser->pSouth != nullptr)
			{
				traverser = traverser->pSouth;
				if (traverser->pWest != nullptr)
				{
					traverser = traverser->pWest;
					if (traverser->pWest != nullptr)
					{
						traverser = traverser->pWest;
						// we are at the node directly south of the deleting node
						nodeSouth = traverser;
						if (traverser->pWest != nullptr)
						{
							traverser = traverser->pWest;
							if (traverser->pNorth != nullptr)
							{
								traverser = traverser->pNorth;
								// we are at the node directly west of the deleting node
								nodeWest = traverser;
							}
						}
					}
				}
			}
		}
	}
}



/*	oddRowEvenColLoops
*		we are going through the four possible loops to find nodes in all directions
*		of the node we are deleting
* if we are in an odd row, we are moving west
* if we are in an even colomn, we only need the east and west nodes
*				node
*				 ^
*		node <  node  <  node
*				 v
*				node
* the loops we could take are:
*	south, east, north, west
*	north, east, south, west
*	west, west, north, east, east, east, south, west
*	west, west, south, east, east, east, north, west
*/
void oddRowEvenColLoops(Node*& traverser, Node*& nodeNorth, Node*& nodeEast, 
						Node*& nodeSouth, Node*& nodeWest, Node* deletingNode)
{
	// loop 1 : south, east, north, west
	if (traverser->pSouth != nullptr)
	{
		traverser = traverser->pSouth;
		// we are at the node directly south of deleting node
		nodeSouth = traverser;
		if (traverser->pEast != nullptr)
		{
			traverser = traverser->pEast;
			if (traverser->pNorth != nullptr)
			{
				traverser = traverser->pNorth;
				// we are at the node directly east of our deleting node
				nodeEast = traverser;
			}
		}
	}
	// traverser may be set to elsewhere in the chain, so reset traverser
	traverser = deletingNode;

	// loop 2 : north, east, south, west
	if (traverser->pNorth != nullptr)
	{
		traverser = traverser->pNorth;
		// we are at the node directly north of our deleting node
		nodeNorth = traverser;
		if (traverser->pEast != nullptr)
		{
			traverser = traverser->pEast;
			if (traverser->pSouth != nullptr)
			{
				traverser = traverser->pSouth;
				// we are at the node directly east of our deleting node
				nodeEast = traverser;
			}
		}
	}
	// traverser may be set to elsewhere in the chain, so reset traverser
	traverser = deletingNode;

	// loop 3 : west, west, north, east, east, east, south, west
	if (traverser->pWest != nullptr)
	{
		traverser = traverser->pWest;
		// we are at the node directly west of our deleting node
		nodeWest = traverser;
		if (traverser->pWest != nullptr)
		{
			traverser = traverser->pWest;
			if (traverser->pNorth != nullptr)
			{
				traverser = traverser->pNorth;
				if (traverser->pEast != nullptr)
				{
					traverser = traverser->pEast;
					if (traverser->pEast != nullptr)
					{
						traverser = traverser->pEast;
						// we are at the node directly north of the deleting node
						nodeNorth = traverser;
						if (traverser->pEast != nullptr)
						{
							traverser = traverser->pEast;
							if (traverser->pSouth != nullptr)
							{
								traverser = traverser->pSouth;
								// we are at the node directly east of the deleting node
								nodeEast = traverser;
							}
						}
					}
				}
			}
		}
	}
	// traverser may be set to elsewhere in the chain, so reset traverser
	traverser = deletingNode;

	// loop 4 : west, west, south, east, east, east, north, west
	if (traverser->pWest != nullptr)
	{
		traverser = traverser->pWest;
		// we are at the node directly west of our deleting node
		nodeWest = traverser;
		if (traverser->pWest != nullptr)
		{
			traverser = traverser->pWest;
			if (traverser->pSouth != nullptr)
			{
				traverser = traverser->pSouth;
				if (traverser->pEast != nullptr)
				{
					traverser = traverser->pEast;
					if (traverser->pEast != nullptr)
					{
						traverser = traverser->pEast;
						// we are at the node directly south of the deleting node
						nodeSouth = traverser;
						if (traverser->pEast != nullptr)
						{
							traverser = traverser->pEast;
							if (traverser->pNorth != nullptr)
							{
								traverser = traverser->pNorth;
								// we are at the node directly east of the deleting node
								nodeEast = traverser;
							}
						}
					}
				}
			}
		}
	}
}


/*	oddRowOddColLoops
*		we are going through the four possible loops to find nodes in all directions
*		of the node we are deleting
* if we are in an odd row, we are moving west
* if we are in an odd column, we need nodes in every direction
*				node
*				 v
*		node <  node  <  node
*				 ^
*				node
* the loops we could take are:
*	west, north, east, south
*	west, south, east, north
*	west, north, east, east, east, south, west, west
*	west, south, east, east, east, north, west, west
*/
void oddRowOddColLoops(Node*& traverser, Node*& nodeNorth, Node*& nodeEast, 
						Node*& nodeSouth, Node*& nodeWest, Node* deletingNode)
{
	// loop 1 : west, north, east, south
	if (traverser->pWest != nullptr)
	{
		traverser = traverser->pWest;
		// we are at the node directly west of the node we are deleting
		nodeWest = traverser;
		if (traverser->pNorth != nullptr)
		{
			traverser = traverser->pNorth;
			if (traverser->pEast != nullptr)
			{
				traverser = traverser->pEast;
				// we are at the node directly north of the node we are deleting
				nodeNorth = traverser;
			}
		}
	}
	// traverser may be set to elsewhere in the chain, so reset traverser
	traverser = deletingNode;

	// loop 2 : west, south, east, north
	if (traverser->pWest != nullptr)
	{
		traverser = traverser->pWest;
		// we are at the node directly west of the node we are deleting
		nodeWest = traverser;
		if (traverser->pSouth != nullptr)
		{
			traverser = traverser->pSouth;
			if (traverser->pEast != nullptr)
			{
				traverser = traverser->pEast;
				// we are at the node directly south of the node we are deleting
				nodeSouth = traverser;
			}
		}
	}
	// traverser may be set to elsewhere in the chain, so reset traverser
	traverser = deletingNode;

	// loop 3 : west, north, east, east, east, south, west, west
	if (traverser->pWest != nullptr)
	{
		traverser = traverser->pWest;
		// we are at the node directly west of the node we are deleting
		nodeWest = traverser;
		if (traverser->pNorth != nullptr)
		{
			traverser = traverser->pNorth;
			if (traverser->pEast != nullptr)
			{
				traverser = traverser->pEast;
				// we are at the node directly north of the node we are deleting
				nodeNorth = traverser;
				if (traverser->pEast != nullptr)
				{
					traverser = traverser->pEast;
					if (traverser->pEast != nullptr)
					{
						traverser = traverser->pEast;
						if (traverser->pSouth != nullptr)
						{
							traverser = traverser->pSouth;
							if (traverser->pWest != nullptr)
							{
								traverser = traverser->pWest;
								// we are at the node directly east of the node we are deleting
								nodeEast = traverser;
							}
						}
					}
				}
			}
		}
	}
	// traverser may be set to elsewhere in the chain, so reset traverser
	traverser = deletingNode;

	// loop 4 : west, south, east, east, east, north, west, west
	if (traverser->pWest != nullptr)
	{
		traverser = traverser->pWest;
		// we are at the node directly west of the node we are deleting
		nodeWest = traverser;
		if (traverser->pSouth != nullptr)
		{
			traverser = traverser->pSouth;
			if (traverser->pEast != nullptr)
			{
				traverser = traverser->pEast;
				// we are at the node directly south of the node we are deleting
				nodeSouth = traverser;
				if (traverser->pEast != nullptr)
				{
					traverser = traverser->pEast;
					if (traverser->pEast != nullptr)
					{
						traverser = traverser->pEast;
						if (traverser->pNorth != nullptr)
						{
							traverser = traverser->pNorth;
							if (traverser->pWest != nullptr)
							{
								traverser = traverser->pWest;
								// we are at the node directly east of the node we are deleting
								nodeEast = traverser;
							}
						}
					}
				}
			}
		}
	}
}


/*	updateBoarderNodes
*		we update the pointers of the nodes north, east, south, and west of the 
*		node we are deleting to account for us deleting the node
*/
void updateBoarderNodes(Node*& nodeNorth, Node*& nodeEast, Node*& nodeSouth, Node*& nodeWest)
{
	if (nodeNorth != nullptr)
	{
		// check if nodeNorth has a pSouth pointer to begin with
		if (nodeNorth->pSouth != nullptr)
		{
			// it does have a pSouth pointer, so update it to nodeSouth (which may be nullptr)
			nodeNorth->pSouth = nodeSouth;
		}
	}
	if (nodeSouth != nullptr)
	{
		// check if nodeSouth has a pNorth pointer to begin with
		if (nodeSouth->pNorth != nullptr)
		{
			// it does have a pNorth pointer, so update it to nodeNorth (may be nnullptr)
			nodeSouth->pNorth = nodeNorth;
		}
	}
	if (nodeEast != nullptr)
	{
		// check if nodeEast has a pWest pointer to begin with
		if (nodeEast->pWest != nullptr)
		{
			// it does have a pWest pointer, so update it to nodeWest (may be nullptr)
			nodeEast->pWest = nodeWest;
		}
	}
	if (nodeWest != nullptr)
	{
		// check if nodeWest has a pEast pointer to begin with
		if (nodeWest->pEast != nullptr)
		{
			// it does have a pEast pointer, so update it to nodeEast (may be nullptr)
			nodeWest->pEast = nodeEast;
		}
	}
}


/*	deleteNode
*		update pHead if we are deleting the pHead node
*		or else we just make all pointers coming out of the node nullptr
*		then delete the node itself
*/
void deleteNode(Node*& deletingNode, Node*& pHead)
{
	assert(deletingNode != nullptr);

	if (deletingNode == pHead)
	{
		// we are deleting the head node, we need move the 
		// head to the pEast node (even if it is nullptr)
		pHead = deletingNode->pEast;
	}

	deletingNode->pNorth = nullptr;
	deletingNode->pEast = nullptr;
	deletingNode->pSouth = nullptr;
	deletingNode->pWest = nullptr;

	delete deletingNode;
}
// ---  End of File ---

