/* **************************************************************************************************************
 
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
 
 *************************************************************************************************************** */

#include<iostream>
#include<map>
#include<set>
using namespace std;

/* Following command defines a set of all vertices in the Graph. "Set" automatically removes repetitions */

set<int> vertices;

/* A pair of vertices defines an edge; That is the vertices are the endpoints of the edge
 Endpoints of all edges and the corresponding edge lengths defines the Graph completely */

map<pair<int, int>,int> Graph;

/* Following command defines the set of all neighbors of a node. This info is stored in a map container class */

map<int, set<int> > neighbours;

map<int, int> Dijkdist;


/* creategraph() is a function that takes the no. of edges and connectivity info. as input and creates a graph */

void creategraph()
{
    int E;                                       // Define a variable that stores the value of no. of edges in a graph
    int lnode, rnode, dist;                      // lnode, rnode are two endpoints of an edge whose length is dist
    cout << "Enter Number of Edges: ";
    cin >> E;                                    // Ask user to input number of edges
    for(int i=0;i<E;i++)
    {
        cout << "Enter Connectivity Information (Index1 Index2 Distance) for Edge No. " << i+1 << " : ";
        
        cin >> lnode >> rnode >> dist;           // Ask user to input connectivity matrix for each edge
        Graph[make_pair(lnode,rnode)] = dist;    // Add Edge to graph
        Graph[make_pair(rnode,lnode)] = dist;    // Connectivity is symmetric
        vertices.insert(lnode);                  // Add lnode to the set of all vertices
        vertices.insert(rnode);                  // Add rnode to the set of all vertices
        neighbours[lnode].insert(rnode);         // Add rnode to the set of all neighbours of lnode
        neighbours[rnode].insert(lnode);         // Add lnode to the set of all neighbours of rnode
        Dijkdist[lnode]=INT_MAX;
        Dijkdist[rnode]=INT_MAX;
    }
}

/* find the index of a node (in a set of nodes) with the shortest from the source */

int minDijkdist(set<int> nodes)
{
    multimap<int, int> Dijkmm;
    multimap<int, int>::iterator itmm;
    set<int>::iterator itnode;
    for(itnode = nodes.begin();itnode!=nodes.end();++itnode)
    {
        
        Dijkmm.insert(make_pair(Dijkdist[*itnode],*itnode));
    }
    itmm = Dijkmm.begin();
    return (*itmm).second;
    
}

/* Function that computes the shortest distance between start and end node given the connectivity information */

int Dijkstra(int start, int end)
{
    set<int>::iterator itset;                   // Define iterator for the set of vertices
    set<int>::iterator neighit;                 // Define iterator for the set of neighbouring vertices
    Dijkdist[start] = 0;
    int vertex, mindistindex;
    int mindist, newdist;
    itset = vertices.find(start);

    while(!vertices.empty())                    // Loop over vertices
    {
        vertex = *itset;                        // Stores the index of the vertex with min distance
        mindist = Dijkdist[vertex];             // Shortest distance from start to vertex
        
        /* Since we have already computed the shortest distance from start to this vertex, ee don't want to 
         revisit this vertex after this point. So we have to remove it from the set of all vertices that 
         needs to be examined. */
        
        vertices.erase(itset);                  // Remove vertex from set of all vertices.
        
        /* Loop over all neighbours of vertex */
        
        for(neighit = neighbours[vertex].begin();neighit!= neighbours[vertex].end();++neighit)
        {
            /* Only neighbours that are present in the set of vertices, needs to be examined */
            if(vertices.find(*neighit)!=vertices.end())
            {
                /* Compute newdistance from start to vertex */
                newdist = mindist + Graph[make_pair(vertex, *neighit)];
                
                /* If the newdistance is shorter than the previously computed value, change the shortest distance to 
                 the new value of shortest distance. */
                
                if(newdist < Dijkdist[*neighit])
                {
                    Dijkdist[*neighit] = newdist;
                }
            }
            
            /* Find the index of the vertex in vertices with the smallest value of Dijkdist.  */
            if(!vertices.empty())
            {
                mindistindex = minDijkdist(vertices);
                itset = vertices.find(mindistindex);
            }
            /* The value of Dijkdist[mindistindex] is the minimum distance from start to mindistindex.
             itset is a pointer to this index. */
            
        }
        
        
    }
    /* At the end of this loop, we would have computed the shortest distance from start to all vertices */
    return Dijkdist[end];                       // Return the shortest distance from
    
}

int main()
{
    int start, end;
    creategraph();                              // Create Graph
    cout << "\nEnter Index of the starting node: ";
    cin >> start;
    cout << "Enter Index of the final node: ";
    cin >> end;
    cout << "Shortest distance between start and end = " << Dijkstra(start, end) << "\n";
    return 0;
}
