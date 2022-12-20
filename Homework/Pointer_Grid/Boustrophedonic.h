//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef BOUSTROPHEDIC_H
#define BOUSTROPHEDIC_H

#include "Node.h"

void Remove(Node *&head, int row, int col);

/* MY CODE - HELPER METHODS */
void checkEven(int row, int col, bool& rowIsEven, bool& colIsEven);
void findClosestEvenRow(int row, int& closestEvenRow);
void moveToClosestEvenRow(Node*& traverser, int closestEvenRow);
void moveToCol(Node*& traverser, int col);
void moveToNextRow(bool colIsEven, Node*& traverser);
void updatePointers(Node*& pHead, int row, int col);
void evenRowEvenColLoops(Node*& traverser, Node*& nodeNorth, Node*& nodeEast, Node*& nodeSouth, Node*& nodeWest, Node* deletingNode);
void evenRowOddColLoops(Node*& traverser, Node*& nodeNorth, Node*& nodeEast, Node*& nodeSouth, Node*& nodeWest, Node* deletingNode);
void oddRowEvenColLoops(Node*& traverser, Node*& nodeNorth, Node*& nodeEast, Node*& nodeSouth, Node*& nodeWest, Node* deletingNode);
void oddRowOddColLoops(Node*& traverser, Node*& nodeNorth, Node*& nodeEast, Node*& nodeSouth, Node*& nodeWest, Node* deletingNode);
void updateBoarderNodes(Node*& nodeNorth, Node*& nodeEast, Node*& nodeSouth, Node*& nodeWest);
void deleteNode(Node*& deletingNode, Node*& pHead);
/* END OF MY CODE*/

#endif

// ---  End of File ---

