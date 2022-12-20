Linked List

Homework meant to check our doubly linked list chops. 
This assignment is meant to simulate a Chicago Hot Dog Stand. 
There are three separate classes:
  HotDog
  Order
  Stand
The Stand class holds and manages a doubly linked list of Orders.
The Order class holds and manages a doubly linked list of HotDogs.
The HotDog class has 8-bit condiments and utilizes bitwise operators. 

What I did:
I wrote the big four for each class (constructor, copy constructor, assignment operator, and destructor),
as well as any other needed helper methods or added functions. For HotDog, I had to write the Add and Minus functions
that utilize bitwise operators to add or remove condiments from a hotdog. For Order, I had to write specific order addition
methods since when a HotDog is added to the Order, the HotDog should go at the end of the Orders doubly linked list of HotDogs.
Order also needed Add and Remove functions that can add or remove a HotDog from the double linked list
of HotDogs belonging to the Order. For Stand, we needed Add and Remove functions as well that takes care of adding and removing Orders
from the Stand's doubly linked list of Orders. We also needed an add Order funtion since the order of orders matters 
(if Stephen puts an order in before Gab then Stephen should be ahead of Gab) so we need to add the new Order to the front of the doubly
linked list of Orders belonging to the Stand.
