//oriasoffer8@gmail.com
#include "graph/Graph.h"
#include "graph/Algorithms.h"
#include <iostream>

using namespace std;
using namespace graph;

int main() {
    Graph g(6);          //create an unweighted graph with 6 vertices and add edges, some forming cycles
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);     //cycle: 0-1-2
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 0);     //cycle: 0-5-4-3-1-0

    Graph weightedGraph(6);   //create a weighted graph with the same structure but weighted edges
    weightedGraph.addEdge(0, 1, 1);
    weightedGraph.addEdge(0, 2, 4);
    weightedGraph.addEdge(1, 2, 2);
    weightedGraph.addEdge(1, 3, 5);
    weightedGraph.addEdge(2, 3, 3);
    weightedGraph.addEdge(3, 4, 2);
    weightedGraph.addEdge(4, 5, 1);


    cout << "Original graph:" << endl;
    g.print_graph();

    cout << "\nBFS Tree from node 0:" << endl;
    Graph bfsTree = Algorithms::bfs(g, 0);
    bfsTree.print_graph();

    cout << "\nDFS Tree from node 0:" << endl;
    Graph dfsTree = Algorithms::dfs(g, 0);
    dfsTree.print_graph();

    std::cout << "\nWeighted graph:" << std::endl;
    weightedGraph.print_graph();
    
    // בדיקה של דייקסטרה
    std::cout << "\nDijkstra Tree from node 0 (weighted):" << std::endl;
    Graph dijkstraWeighted = Algorithms::dijkstra(weightedGraph, 0);
    dijkstraWeighted.print_graph();
    
    std::cout << "\nPrim MST from weighted graph:" << std::endl;
    Graph primTree = Algorithms::prim(weightedGraph);
    primTree.print_graph();

    std::cout << "\nKruskal MST from weighted graph:" << std::endl;
    Graph kruskalTree = Algorithms::kruskal(weightedGraph);
    kruskalTree.print_graph();
    


    return 0;
}
