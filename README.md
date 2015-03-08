# GraphTriangle
g++ GraphTriangle.cpp -o GraphTriangle.o

This code counts the number of triangles in a graph given the "direct" connectivity information.
Nodes that are not directly connected are assumed to be separated by infinite "direct" ditance.

For example:

Consider a graph with 4 edges and the following connectivity information.
 
 i j d(i,j)
 
 1 2 5
 
 2 3 4
 
 1 3 10
 
 3 4 8
 
The connectivity information is specified by specifying the indices of the two endpoints of an edge(i and j),
followed by the diatance, d(i,j).
 
Only nodes 1,2 and 3 form a triangle. Note that the triangle inequality need not be satisfied. We just define
a triangle as an abstract entity with three vertices that are pairwise connected.

# Dijkstra
g++ Dijkstra.cpp -o Dijkstra.o

This code computes the shortest distance between two nodes of a graph given the "direct"
connectivity information. Nodes that are not directly connected are assumed to be separated
by infinite "direct" ditance.
 
 For example:
 
 Consider a graph with 4 edges and the following connectivity information. The connectivity information is 
 specified by specifying the indices of the two endpoints of an edge(i and j), followed by the diatance, 
 d(i,j).
 
 i j d(i,j)
 
 1 2 5
 
 2 4 3
 
 1 3 2
 
 1 4 25
 
 The shortest distance between Node No. 1 and Node No. 4 is 8.
