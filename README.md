# RiverCrossing
For this programming assignment I used recursive maze runner. With the nature of turns, there were 8 directions (10 if you include the different types of up and downs). Moving to a node with a 0 value costs 2, and moving to a node with a 1 value costs 1. However if moving up and down moving to a node with 1 costs 0. You can only move to adjacent or diagonal nodes in my algorithm. The speed complexity is highly dependent on the layout of the boards, but its best case is O(M * (N - 1)) and worst case roughly O(M^2 * (N - 1)). After passing the given test cases I generated test cases of large dimension to test speed complexity and other edge cases. The space complexity is O(M * (N-1)) to store the matrix of nodes and recursive calls. 

Speed Complexity: 	O(M^2 * (N - 1)) On some board layouts
			O(M * (N - 1)) On some board layouts
			*When there are many 1’s more directions can be traveled because quick
			up and quick down are called more often and additional rows may need 
			to be rechcked
Space Complexity:	O(M * (N - 1))

Algorithm:
The pathing has the following priority. Free up, Free down, up + right, right, down + right, up, down, up + left, left, down + left for a total of 10 directions. Going left and then up can give a different result from traveling vertically which is why 8 directions is justified. Moving up and down can either be free or cost, when free up and down are high priority so 10 directions. The goal is to modify nodes that can have their current value replaced with a smaller value. Originally the board was initialized to INT_MAX meaning that there could be potentially be over M * (N - 1) recursive stacks. I optimized my code by initializing the values as if I traversed the matrix horizontally and set values accordingly. By doing so many of the nodes will be initialized to low values from the start and much fewer recursive stacks are needed. This increased my speed by roughly 10% on most test cases and allowed me to run test cases with N and M over 10,000.
