Pointer Grid

Interesting little assigment to test our pointer skills.
We are given a grid of nodes that follows a specific pattern:
Starting at row 0, row 0 points east, row 1 points west, row 2 points east, etc.
The columns follow a pattern where each node alternates pointing north and south away from itself, 
and pointing north and south towards itself.
So the grid looks something like this:
node > node > node > node > node > node
  ^     v       ^     v      ^       v     
node < node < node < node < node < node
  v     ^       v     ^      v       ^
node > node > node > node > node > node

and so on, where in this demo all directions (> < ^ v)
are pointers. Our goal of the assignment was to remove a node in the most
optimal fashion. 

What I did:
I first traversed north / south to get to the closest even row to the row
that had the node to be deleted (so this was either the row itself or the row above). 
I went to the even row because the even rows point east, so my next step could be moving east 
to the exact column of the node that is being deleted. Now we are either at the node to be 
deleted, or at the node directly above the node that is being deleted. We can easily go south 
to get to the needed node if we are above it. 
Now before deletion we needed to follow all possible loops around the to-be-deleted node to make
sure we fix pointers. There are only so many paths you need to take (4 to be exact) in order to get
to all nodes surrounding out to-be-deleted node. We traverse all these paths, making sure to updated 
pointers to point past the to-be-deleted node. Then finally, we can delete the proper node and still
have the pointer grid function.
