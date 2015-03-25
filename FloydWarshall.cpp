/* **************************************************************************************************************
 
 This code computes all pairs shortest distance of a graph using Floyd-Warshall algorithm, given the "direct"
 connectivity information. Nodes that are not directly connected are assumed to be separated by infinite "direct"
 ditance.
 
 For example:
 
 Consider a graph with 4 edges and the following connectivity information. The connectivity information is
 specified by specifying the indices of the two endpoints of an edge(i and j), followed by the diatance,
 d(i,j).
 
 i j d(i,j)
 1 2 5
 2 4 3
 1 3 2
 1 4 25
 

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
map<pair<int, int>, int > label;
set<int> path;
int main()
{
    int start, end;
    map<pair<int, int>, int > dis;
    int E;                                       // Define a variable that stores the value of no. of edges in a graph
    int lnode, rnode, w;                        // lnode, rnode are two endpoints of an edge whose length is dist
    cout << "Enter Number of Edges: ";
    cin >> E;                                    // Ask user to input number of edges
    map<pair<int, int>,int>::iterator it;
    for(int i=0;i<E;i++)
    {
        cout << "Enter Connectivity Information (Index1 Index2 Distance) for Edge No. " << i+1 << " : ";
        
        cin >> lnode >> rnode >> w;             // Ask user to input connectivity matrix for each edge
        Graph[make_pair(lnode,rnode)] = w;      // Add Edge to graph
        Graph[make_pair(rnode,lnode)] = w;      // Connectivity is symmetric
        vertices.insert(lnode);                 // Add lnode to the set of all vertices
        vertices.insert(rnode);                 // Add rnode to the set of all vertices
    }
    cout << "\nEnter Index of the starting node: ";
    cin >> start;
    cout << "Enter Index of the final node: ";
    cin >> end;
    
    int vsize = vertices.size();
    set<int>:: iterator seti, setj, setk, labit;
    /* Initialize the distances and path */
    for(seti=vertices.begin();seti!=vertices.end();++seti)
    {
        for(setj=vertices.begin();setj!=vertices.end();++setj)
        {
            it = Graph.find(make_pair(*seti,*setj));    // iterator to check if a pair of vertices are neighbors
            dis[make_pair(*seti,*setj)] = INT_MAX;      // Initialize distance between nodes to infinity
            if(it!=Graph.end())
            {
                /* If the two nodes are neighbors then initialize the distance to the edge length */
                dis[make_pair(*seti,*setj)] = Graph[make_pair(*seti,*setj)];
                dis[make_pair(*seti,*setj)] = Graph[make_pair(*seti,*setj)];
                /* If the two nodes are neighbors then initialize the path to the last node */
                label[make_pair(*seti,*setj)] = *setj;
            }
        }
    }
    /* For coincident nodes, the distance is zero */
    for(seti=vertices.begin();seti!=vertices.end();++seti)
    {
        dis[make_pair(*seti,*seti)] = 0;
    }
    /* Following is the main part of Floyd-Warshall Algorithm. Ordering of the loops is important */
    for(setk=vertices.begin();setk!=vertices.end();++setk)
    {
        for(seti=vertices.begin();seti!=vertices.end();++seti)
        {
            for(setj=vertices.begin();setj!=vertices.end();++setj)
            {
                if((dis[make_pair(*seti,*setk)]!=INT_MAX) && (dis[make_pair(*setk,*setj)]!=INT_MAX))
                {
                    if(dis[make_pair(*seti,*setj)]>dis[make_pair(*seti,*setk)]+dis[make_pair(*setk,*setj)])
                    {
                        dis[make_pair(*seti,*setj)] = dis[make_pair(*seti,*setk)]+dis[make_pair(*setk,*setj)];
                        label[make_pair(*seti,*setj)] = label[make_pair(*seti,*setk)];
                    }
                }
            }
        }
    }
    
    cout << "Shortest Distance =" <<dis[make_pair(start,end)] << "\n";
    cout << "The shortest path is : \n" ;
    int var = start;
    while(var!=end)
    {
        cout << var << " ";
        var= label[make_pair(var,end)];
    }
    cout << end << "\n";
    return 0;
}
