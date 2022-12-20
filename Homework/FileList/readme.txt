FileList

This assignment was to write a load in place file using a contiguous memory footprint.
We had to take a doubly linked list of nodes, write them contiguously to a binary file,
then load that data from the binary file into one memory block, then fix the memory pointers
to recreate the doubly linked list. We were only allowed to use one call to "new". 

What I did:
Opened a binary file for writing, then took a given doubly linked list of pointers and used fwrite to 
write all nodes to the binary file (one at a time). Then closed the binary file.
Next I created the FileList constructor using the binary file. I opened the binary file (with error checking).
I created a block of memory that is of size (sizeof(Node) * number of Nodes) and used my NEW call to create a char pointer to point 
to the block of memory so I could access one byte at a time of this contiguous memory block. I fread_s the binary file into this
block of memory. Finally I had to go through this block of memory one byte at a time using pointer arithmetic to move Node size by 
Node size and re-cast each node as a node and fix the pointers to now be pointing to the correct previous / next node locations. 
