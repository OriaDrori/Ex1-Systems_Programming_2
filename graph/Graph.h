//oriasoffer8@gmail.com
#ifndef GRAPH_H
#define GRAPH_H

namespace graph {

class Graph {
private:
    int numVertices;              
    int** adjacencyList;          //array of neighbor lists
    int* listSizes;               //number of neighbors per vertex
    int* listCapacities;          //current capacity of each neighbor list
    int** weightList;             //array holding edge weights

public:
    Graph(int vertices);          //constructor
    ~Graph();                     //destructor

    void addEdge(int src, int dest, int weight = 1); 
    void removeEdge(int src, int dest);              
    void print_graph() const;                       
    int* getNeighbors(int v) const;                  
    int getNeighborCount(int v) const;            
    int getNumVertices() const;                    
    int getNumNeighbors(int u) const;                
    bool hasEdge(int u, int v) const;               
    int getWeight(int u, int v) const;             
};

} 
#endif 
