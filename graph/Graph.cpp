//oriasoffer8@gmail.com
#include "Graph.h"
#include <iostream>
#include <stdexcept>
#include <climits>

namespace graph {

//constructor
Graph::Graph(int vertices) : numVertices(vertices) {
    adjacencyList = new int*[vertices];
    weightList = new int*[vertices];
    listSizes = new int[vertices];
    listCapacities = new int[vertices];
    for (int i = 0; i < vertices; ++i) {
        adjacencyList[i] = new int[2];             //start with capacity for 2 neighbors
        weightList[i] = new int[2];
        listSizes[i] = 0;                          //initially no neighbors
        listCapacities[i] = 2;                 
    }
}

//destructor
Graph::~Graph() {
    for (int i = 0; i < numVertices; ++i) {
        delete[] adjacencyList[i];                
        delete[] weightList[i];                    
    }
    delete[] adjacencyList;
    delete[] weightList;
    delete[] listSizes;
    delete[] listCapacities;
}   

void Graph::addEdge(int src, int dest, int weight) {
    if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices)
        throw std::out_of_range("Invalid vertex index");
    if (src == dest)
        throw std::invalid_argument("Self-loops are not allowed");

    //prevent adding duplicate edge from src to dest
    for (int i = 0; i < listSizes[src]; i++) {
        if (adjacencyList[src][i] == dest)
            return;
    }

    //resize adjacency and weight lists for src if needed
    if (listSizes[src] >= listCapacities[src]) {
        int* newList = new int[listCapacities[src] * 2];
        int* newWeights = new int[listCapacities[src] * 2];
        for (int i = 0; i < listSizes[src]; ++i) {
            newList[i] = adjacencyList[src][i];
            newWeights[i] = weightList[src][i];
        }
        delete[] adjacencyList[src];
        delete[] weightList[src];
        adjacencyList[src] = newList;
        weightList[src] = newWeights;
        listCapacities[src] *= 2;
    }
    adjacencyList[src][listSizes[src]] = dest;      //add neighbor
    weightList[src][listSizes[src]] = weight;       //add weight
    listSizes[src]++;

    //add reverse edge since graph is undirected
    if (listSizes[dest] >= listCapacities[dest]) {
        int* newList = new int[listCapacities[dest] * 2];
        int* newWeights = new int[listCapacities[dest] * 2];
        for (int i = 0; i < listSizes[dest]; ++i) {
            newList[i] = adjacencyList[dest][i];
            newWeights[i] = weightList[dest][i];
        }
        delete[] adjacencyList[dest];
        delete[] weightList[dest];
        adjacencyList[dest] = newList;
        weightList[dest] = newWeights;
        listCapacities[dest] *= 2;
    }
    adjacencyList[dest][listSizes[dest]] = src;     
    weightList[dest][listSizes[dest]] = weight;      
    ++listSizes[dest];
}

//remove an undirected edge between src and dest
void Graph::removeEdge(int src, int dest) {
    if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices){
        throw std::out_of_range("Invalid vertex index");
    }
    bool removed = false;
    for (int i = 0; i < listSizes[src]; i++) {
        if (adjacencyList[src][i] == dest) {
            adjacencyList[src][i] = adjacencyList[src][listSizes[src] - 1];  //replace the removed edge with the last element
            weightList[src][i] = weightList[src][listSizes[src] - 1];
            listSizes[src]--;
            removed = true;
            break;
        }
    }
    //remove reverse edge dest -> src
    for (int i = 0; i < listSizes[dest]; ++i) {
        if (adjacencyList[dest][i] == src) {
            adjacencyList[dest][i] = adjacencyList[dest][listSizes[dest] - 1];
            weightList[dest][i] = weightList[dest][listSizes[dest] - 1];
            listSizes[dest]--;
            break;
        }
    }
    if (!removed)
        throw std::invalid_argument("Edge does not exist");
}

//get total number of vertices in the graph
int Graph::getNumVertices() const {
    return numVertices;
}

//return pointer to neighbors of vertex u
int* Graph::getNeighbors(int u) const {
    if (u < 0 || u >= numVertices)
        throw std::out_of_range("Invalid vertex index");
    return adjacencyList[u];
}

//return number of neighbors of vertex u
int Graph::getNumNeighbors(int u) const {
    if (u < 0 || u >= numVertices)
        throw std::out_of_range("Invalid vertex index");
    return listSizes[u];
}

//return weight of edge u -> v
int Graph::getWeight(int u, int v) const {
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
        throw std::out_of_range("Invalid vertex index");
    for (int i = 0; i < listSizes[u]; ++i) {
        if (adjacencyList[u][i] == v) {
            return weightList[u][i];
        }
    }
    return INT_MAX;
}

//check if edge u-v exists in the graph
bool Graph::hasEdge(int u, int v) const {
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
        return false;
    for (int i = 0; i < listSizes[u]; i++) {
        if (adjacencyList[u][i] == v) {
            return true;
        }
    }
    return false;
}

//print the adjacency list representation of the graph
void Graph::print_graph() const {     //does not modify the object
    for (int i = 0; i < numVertices; i++) {
        std::cout << i << ":";
        for (int j = 0; j < listSizes[i]; j++) {
            std::cout << " " << adjacencyList[i][j] << "(" << weightList[i][j] << ")";
        }
        std::cout << std::endl;
    }
}

} 
