/*
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
*/


#include<iostream>
#include<map>
#include<set>
using namespace std;

set<int> vertices; //Defines a set of all vertices in the Graph. Using "set" datastructure automatically removes repetitions
map<pair<int, int>,int> Graph; // A pair of vertices defines an edge; That is the vertices are the endpoints of the edge
                               // Endpoints of all edges and the corresponding edge lengths defines the Graph completely

void creategraph() //Function that takes the number of edges and connectivity information as input and creates a graph
{
    int E;
    int lnode, rnode, dist;
    cout << "Enter Number of Edges: ";
    cin >> E; //Ask user to input number of edges
    for(int i=0;i<E;i++)
    {
        cout << "Enter Connectivity Information (Index1 Index2 Distance) for Edge" << i+1 << " : ";
        cin >> lnode >> rnode >> dist;                              //Ask user to input connectivity matrix for each edge
        Graph[make_pair(lnode,rnode)] = dist;                       //Add Edge to graph
        Graph[make_pair(rnode,lnode)] = dist;                       //Connectivity is symmetric
        vertices.insert(lnode);                                     //Add vertices to the set
        vertices.insert(rnode);
    }
}
int countTriangles()                            // Function that counts the traingles in a graph using connectivity matrix
{
    int countTr =0;                             // Initialize Count Triangles
    set<int>::iterator itset;                   // Define iterator for the set of vertices
    map<pair<int, int>,int>::iterator itmap, itfind1, itfind2; // Define iterators for the graph
    int vertex, vertex1, vertex2;               // A triplet of vertices. We will use these variables to check if they form a traingle
    for(itset = vertices.begin(); itset!=vertices.end();++itset) //Loop over vertices
    {
        vertex = *itset;                        // Store an element of the vertices
        for(itmap = Graph.begin(); itmap!=Graph.end();++itmap) //Loop over edges
        {
            vertex1=itmap->first.first;         // First vertex of an edge
            vertex2=itmap->first.second;        // Second vertex of an edge
            itfind1 = Graph.find(make_pair(vertex,vertex1)); //1. Check if the vertex of the set and first vertex of the edge is connected
            itfind2 = Graph.find(make_pair(vertex,vertex2)); //2. Check if the vertex of the set and second vertex of the edge is connected
            if((itfind1!=Graph.end())&&(itfind2!=Graph.end())) //If both conditions are satisfied then increment the number of triangles
            {
                
                countTr++;
            }
        }
    }
    return countTr/6; // Divide by a factor of 6 to eliminate overcounting from looping over the 6 permutations of the vertices
    
}
int main()
{
    creategraph(); //Create Graph
    cout << "Number of triangles in the graph = " << countTriangles() << "\n"; //Count number of triangles in the graph
    return 0;
}
