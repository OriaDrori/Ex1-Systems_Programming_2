//oriasoffer8@gmail.com
#include "Algorithms.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include <climits>
#include <iostream>
#include "UnionFind.h"

namespace graph {

//builds a tree starting from start node using a queue.
Graph Algorithms::bfs(const Graph& g, int start) {   // The input graph is passed as a const to avoid copying and ensure immutability.
    if (start < 0 || start >= g.getNumVertices()) {
        throw std::out_of_range("Start node is out of graph bounds.");
    }
    int n = g.getNumVertices();
    Graph tree(n);
    bool* visited = new bool[n]();
    Queue q(n);
    visited[start] = true;
    q.enqueue(start);
    while (!q.isEmpty()) {
        int current = q.dequeue();
        int* neighbors = g.getNeighbors(current);
        int neighborCount = g.getNumNeighbors(current);
        for (int i = 0; i < neighborCount; i++) {
            int neighbor = neighbors[i];
            // visit only unvisited nodes and add to BFS tree
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                tree.addEdge(current, neighbor, 1);
                q.enqueue(neighbor);   //enqueue the neighbor for future exploration
            }
        }
    }
    delete[] visited;     //memory release
    return tree;
}

// recursive helper function for DFS
void dfsHelper(const Graph& g, Graph& tree, int current, bool* visited) {
    visited[current] = true;
    int neighborCount = g.getNumNeighbors(current);
    int* neighbors = g.getNeighbors(current);
    for (int i = 0; i < neighborCount; i++) {
        int neighbor = neighbors[i];
        // visit only unvisited nodes and add to DFS tree
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            tree.addEdge(current, neighbor, 1);
            dfsHelper(g, tree, neighbor, visited);
        }
    }
}

//builds a DFS tree using recursion
Graph Algorithms::dfs(const Graph& g, int start) {
    if (start < 0 || start >= g.getNumVertices()) {
        throw std::out_of_range("Start node is out of graph bounds.");
    }
    int n = g.getNumVertices();
    Graph tree(n);
    bool* visited = new bool[n]();
    //start DFS from the given start node
    if (start >= 0 && start < n) {
        dfsHelper(g, tree, start, visited);
    }
    //continue DFS from every unvisited node to ensure the entire graph is covered
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfsHelper(g, tree, i, visited);
        }
    }
    delete[] visited;   //memory release
    return tree;
}

//builds shortest path tree using priority queue
Graph Algorithms::dijkstra(const Graph& graph, int source) {
    int n = graph.getNumVertices();
    Graph spTree(n);
    int* dist = new int[n];       //stores the shortest known distance from source to each vertex
    int* parent = new int[n];
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[source] = 0;
    PriorityQueue pq(n);
    pq.push(source, 0);
    while (!pq.isEmpty()) {
        int u = pq.pop();
        if (u < 0 || u >= n) {
            std::cerr << "Invalid vertex index extracted from priority queue: " << u << std::endl;
            continue; 
        }
        int neighborCount = graph.getNumNeighbors(u);
        int* neighbors = graph.getNeighbors(u);
        for (int i = 0; i < neighborCount; i++) {
            int v = neighbors[i];
            int weight = graph.getWeight(u, v);
            if (weight < 0) {
                delete[] dist;
                delete[] parent;
                throw std::invalid_argument("Negative weights are not allowed in Dijkstra's algorithm");
            }
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;   //update the shortest distance to v
                parent[v] = u;                //record u as the parent of v in the shortest path tree
                if (pq.contains(v)) {
                    pq.decreaseKey(v, dist[v]);     //update v distance in the priority queue
                } else {
                    pq.push(v, dist[v]);           //add v to the queue with its new distance
                }
            }
        }
    }
    //builds the shortest path tree
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1) {
            int weight = graph.getWeight(parent[i], i);
            spTree.addEdge(parent[i], i, weight);
        }
    }
    delete[] dist;     //memory release
    delete[] parent;   //memory release
    return spTree;
}

//builds a minimum spanning tree using priority queue
Graph Algorithms::prim(const Graph& graph) {
    int n = graph.getNumVertices();
    Graph mst(n);
    bool* inMST = new bool[n]();
    int* key = new int[n];      //minimum edge weight to each vertex
    int* parent = new int[n];   //stores parent of each vertex in MST
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }
    key[0] = 0;
    PriorityQueue pq(n);
    pq.push(0, 0);

    while (!pq.isEmpty()) {
        int u = pq.pop();
        inMST[u] = true;
        int neighborCount = graph.getNumNeighbors(u);
        int* neighbors = graph.getNeighbors(u);
        for (int i = 0; i < neighborCount; i++) {
            int v = neighbors[i];
            int weight = graph.getWeight(u, v);
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;      //update the minimum known weight to reach v
                parent[v] = u;        //set u as the parent of v in the MST
                if (pq.contains(v)) {
                    pq.decreaseKey(v, weight);     //update v distance in the priority queue
                } else {
                    pq.push(v, weight);
                }
            }
        }
    }
    //builds the MST
    for (int i = 0; i < n; ++i) {
        if (parent[i] != -1) {
            int weight = graph.getWeight(parent[i], i);
            mst.addEdge(parent[i], i, weight);
        }
    }
    delete[] inMST;        //memory release
    delete[] key;          //memory release
    delete[] parent;       //memory release
    return mst;
}

//builds a minimum spanning tree using sorted edges and Union-Find
Graph Algorithms::kruskal(const Graph& graph) {
    int n = graph.getNumVertices();
    Graph mst(n);
    struct Edge {
        int u, v, w;
    };
    Edge* edges = new Edge[n*n]; //the maximum number of edges possible in a graph of n vertices.
    int edgeCount = 0;
    for (int u = 0; u < n; u++) {
        int* neighbors = graph.getNeighbors(u);
        int count = graph.getNumNeighbors(u);
        for (int i = 0; i < count; i++) {
            int v = neighbors[i];
            if (u < v) { //avoid duplicate edges, the graph is undirected
                int weight = graph.getWeight(u, v);
                edges[edgeCount] = {u, v, weight};
                edgeCount++;
            }
        }
    }
    //sort edges by weight
    for (int i = 0; i < edgeCount - 1; ++i) {
        for (int j = i + 1; j < edgeCount; ++j) {   //compare with next edges
            if (edges[j].w < edges[i].w) {         //swap if current edge is bigger
                Edge tmp = edges[i];
                edges[i] = edges[j];
                edges[j] = tmp;
            }
        }
    }
    UnionFind uf(n);       //initially, each vertex is a group in itself.
    for (int i = 0; i < edgeCount; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (!uf.connected(u, v)) {    //avoid creating a circle
            uf.unionSets(u, v);       //merge the sets of u and v
            mst.addEdge(u, v, w);    
        }
    }
    delete[] edges;      //memory release
    return mst;
}

} 
