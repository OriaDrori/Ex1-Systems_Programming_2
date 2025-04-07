//oriasoffer8@gmail.com
#ifndef ALGORITHMS_H    //header guard to prevent multiple inclusions
#define ALGORITHMS_H

#include "Graph.h"

namespace graph {
    class Algorithms {
    public:
        static Graph bfs(const Graph& g, int start);
        static Graph dfs(const Graph& g, int start);
        static Graph dijkstra(const Graph& graph, int source);
        static Graph prim(const Graph& graph);
        static Graph kruskal(const Graph& graph);

    };
    
}

#endif      //end of header guard
