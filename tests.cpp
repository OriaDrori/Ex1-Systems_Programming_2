//oriasoffer8@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "graph/Graph.h"
#include "graph/Algorithms.h"
#include <iostream>

using namespace graph;

TEST_CASE("basic addEdge and print_graph") {
    std::cout << "\n--- basic addEdge and print_graph ---n";
    Graph g(3);
    CHECK_NOTHROW(g.addEdge(0, 1));
    CHECK_NOTHROW(g.addEdge(1, 2));
    CHECK_NOTHROW(g.addEdge(2, 0));
    g.print_graph();
    CHECK(g.hasEdge(0, 1));
    CHECK(g.hasEdge(1, 0));
}

TEST_CASE("removeEdge valid and invalid edge") {
    std::cout << "\n--- removeEdge valid and invalid ---\n";
    Graph g(3);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    CHECK(g.hasEdge(0, 1));
    CHECK_NOTHROW(g.removeEdge(0, 1));
    CHECK_FALSE(g.hasEdge(0, 1));
    CHECK_THROWS(g.removeEdge(0, 1));
    g.print_graph();
}

TEST_CASE("addEdge with out of range vertices") {
    Graph g(3);
    CHECK_THROWS(g.addEdge(-1, 2));
    CHECK_THROWS(g.addEdge(1, 5));
    CHECK_THROWS(g.addEdge(3, 3));
}

TEST_CASE("removeEdge with out of range vertices") {
    Graph g(3);
    CHECK_THROWS(g.removeEdge(-1, 2));
    CHECK_THROWS(g.removeEdge(1, 5));
    CHECK_THROWS(g.removeEdge(3, 3));
}

TEST_CASE("empty graph print") {
    std::cout << "\n--- empty graph print ---\n";
    Graph g(2);
    CHECK_NOTHROW(g.print_graph());
}

TEST_CASE("self loop edge") {
    Graph g(3);
    CHECK_THROWS(g.addEdge(1, 1));
}

TEST_CASE("graph with single vertex") {
    std::cout << "\n--- graph with single vertex ---\n";
    Graph g(1);
    CHECK_NOTHROW(g.print_graph());
    CHECK(g.getNumVertices() == 1);
    CHECK(g.getNumNeighbors(0) == 0);
    CHECK_THROWS(g.addEdge(0, 0));        // Self looping is prohibited
}

TEST_CASE("graph with multiple vertices and no edges") {
    std::cout << "\n--- graph with multiple vertices and no edges ---\n";
    Graph g(5);
    for (int i = 0; i < 5; ++i) {
        CHECK(g.getNumNeighbors(i) == 0);
    }
    CHECK_NOTHROW(g.print_graph());
}

TEST_CASE("BFS from node 0") {
    std::cout << "\n--- BFS from node 0 ---\n";
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);

    Graph bfsTree = Algorithms::bfs(g, 0);
    CHECK_NOTHROW(bfsTree.print_graph());
    CHECK(bfsTree.hasEdge(0, 1));
    CHECK(bfsTree.hasEdge(0, 2));
    CHECK(bfsTree.hasEdge(1, 3));
    CHECK(bfsTree.hasEdge(1, 4));
    CHECK_FALSE(bfsTree.hasEdge(2, 3));
}

TEST_CASE("BFS from node 3 + out of range") {
    std::cout << "\n--- BFS from 3 + out of range ---\n";
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    
    CHECK_NOTHROW(Algorithms::bfs(g, 3));
    CHECK_THROWS(Algorithms::bfs(g, 10));
    Graph bfs = Algorithms::bfs(g, 3);
    CHECK_NOTHROW(bfs.print_graph());
    CHECK(bfs.hasEdge(3, 1));
    CHECK_FALSE(bfs.hasEdge(0, 2));
}

TEST_CASE("BFS: graph with cycle") {
    std::cout << "\n--- BFS: graph with cycle ---\n";
    graph::Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 0, 1);                //cycle
    g.addEdge(2, 3, 1);

    graph::Graph bfs = graph::Algorithms::bfs(g, 0);
    CHECK_NOTHROW(bfs.print_graph());
    CHECK(bfs.hasEdge(0, 1));
    CHECK(bfs.hasEdge(0, 2));
    CHECK(bfs.hasEdge(2, 3));                      
    CHECK_FALSE(bfs.hasEdge(1, 2));                // this edge closes the cycle and therefore should not be in tree
}

TEST_CASE("DFS from node 0") {
    std::cout << "\n--- DFS from node 0 ---\n";
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(3, 4);

    Graph dfsTree = Algorithms::dfs(g, 0);
    CHECK_NOTHROW(dfsTree.print_graph());
    CHECK(dfsTree.hasEdge(0, 1));
    CHECK(dfsTree.hasEdge(1, 3));
    CHECK(dfsTree.hasEdge(3, 4));
    CHECK_FALSE(dfsTree.hasEdge(1, 4));
    CHECK(dfsTree.hasEdge(0, 2));

}

TEST_CASE("DFS from node 3 + out of range") {
    std::cout << "\n--- DFS from node 3 + out of range ---\n";
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    
    CHECK_NOTHROW(Algorithms::dfs(g, 3));
    CHECK_THROWS(Algorithms::dfs(g, 10));
    
    Graph dfs = Algorithms::dfs(g, 3);
    CHECK_NOTHROW(dfs.print_graph());
    CHECK(dfs.hasEdge(3, 4));
    CHECK(dfs.hasEdge(4, 5));
    CHECK_FALSE(dfs.hasEdge(1, 2));                  
}

TEST_CASE("DFS: graph with cycle") {
    std::cout << "\n--- DFS: graph with cycle---\n";
    graph::Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 0, 1); // cycle
    g.addEdge(2, 3, 1);

    graph::Graph dfs = graph::Algorithms::dfs(g, 0);
    CHECK_NOTHROW(dfs.print_graph());
    CHECK(dfs.hasEdge(0, 1));
    CHECK(dfs.hasEdge(1, 2));
    CHECK_FALSE(dfs.hasEdge(2, 0));                        // this edge closes the cycle and therefore should not be in tree
}

TEST_CASE("disconnected graph: BFS + DFS") {
    std::cout << "\n--- disconnected graph: BFS + DFS ---\n";
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(3, 4);

    Graph bfsTree = Algorithms::bfs(g, 3);
    CHECK_FALSE(bfsTree.hasEdge(0, 1));
    CHECK_FALSE(bfsTree.hasEdge(1, 2));
    CHECK(bfsTree.hasEdge(3, 4));

    Graph dfsTree = Algorithms::dfs(g, 3);
    CHECK(dfsTree.hasEdge(0, 1));
    CHECK(dfsTree.hasEdge(1, 2));
    CHECK(dfsTree.hasEdge(3, 4));

    std::cout << "\n--- BFS ---\n";
    bfsTree.print_graph();

    std::cout << "\n--- DFS ---\n";
    dfsTree.print_graph();
}

TEST_CASE("empty graph: BFS + DFS (no edges)") {
    std::cout << "\n--- empty graph: BFS + DFS (no edges) ---\n";
    Graph g(4);
    Graph bfs = Algorithms::bfs(g, 0);
    Graph dfs = Algorithms::dfs(g, 0);
    CHECK_NOTHROW(bfs.print_graph());
    CHECK_NOTHROW(dfs.print_graph());
    for (int i = 0; i < 4; ++i) {
        CHECK(bfs.getNumNeighbors(i) == 0);
        CHECK(dfs.getNumNeighbors(i) == 0);
    }
}

TEST_CASE("BFS + DFS from invalid node") {
    Graph g(3);
    CHECK_THROWS(Algorithms::bfs(g, -1));
    CHECK_THROWS(Algorithms::dfs(g, 10));
}

TEST_CASE("basic dijkstra") {
    std::cout << "\n--- basic dijkstra ---\n";
    Graph g(6);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 1);

    Graph tree = Algorithms::dijkstra(g, 0);
    CHECK_NOTHROW(tree.print_graph());

    CHECK(tree.hasEdge(0, 1));
    CHECK(tree.hasEdge(1, 2));  // 0→1→2 is shorter than 0→2 directly
    CHECK(tree.hasEdge(1, 3));  // 0→1→2→3 = 1+2+3 = 6
    CHECK(tree.hasEdge(3, 4));
    CHECK(tree.hasEdge(4, 5));
    CHECK_FALSE(tree.hasEdge(0, 2));
}

TEST_CASE("dijkstra on disconnected graph") {
    std::cout << "\n--- dijkstra on disconnected graph ---\n";
    Graph g(4);
    g.addEdge(0, 1, 2);
    Graph tree = Algorithms::dijkstra(g, 0);
    CHECK_NOTHROW(tree.print_graph());
    CHECK(tree.hasEdge(0, 1));
    CHECK_FALSE(tree.hasEdge(2, 3));
    CHECK_FALSE(tree.hasEdge(0, 2));
}

TEST_CASE("dijkstra unreachable node") {
    std::cout << "\n--- dijkstra unreachable node ---\n";
    Graph g(3);
    g.addEdge(0, 1, 1);
    Graph tree = Algorithms::dijkstra(g, 0);
    CHECK_NOTHROW(tree.print_graph());
    CHECK(tree.hasEdge(0, 1));
    CHECK(tree.getNumNeighbors(2) == 0);
}

TEST_CASE("dijkstra on graph with a self loop") {
    std::cout << "--- dijkstra on graph with a self loop ---\n";
    graph::Graph g(3);
    CHECK_THROWS(g.addEdge(0, 0, 1));  // self loop
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 3);

    graph::Graph tree = graph::Algorithms::dijkstra(g, 0);
    CHECK_NOTHROW(tree.print_graph());
    CHECK_FALSE(tree.hasEdge(0, 0));            // self-loop should not be included
    CHECK(tree.hasEdge(0, 1));
    CHECK(tree.hasEdge(1, 2));
}

TEST_CASE("dijkstra on graph with negative weights") {
    graph::Graph g(3);
    g.addEdge(0, 1, -5);                       // dijkstra is invalid for negative weights.
    g.addEdge(1, 2, 2);

    CHECK_THROWS(graph::Algorithms::dijkstra(g, 0)); 
}

TEST_CASE("basic prim") {
    std::cout << "\n--- basic prim ---\n";
    Graph g(6);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 1);

    Graph mst = Algorithms::prim(g);
    CHECK_NOTHROW(mst.print_graph());

    // minimum spanning tree of 6 vertices = 5 edges
    int edgeCount = 0;
    for (int u = 0; u < 6; ++u) {
        edgeCount += mst.getNumNeighbors(u);
    }
    CHECK(edgeCount / 2 == 5);          // every rainbow is counted twice
    CHECK(mst.hasEdge(0, 1));
    CHECK(mst.hasEdge(1, 2));
    CHECK(mst.hasEdge(2, 3));
    CHECK(mst.hasEdge(3, 4));
    CHECK(mst.hasEdge(4, 5));
    CHECK_FALSE(mst.hasEdge(0, 2));
    CHECK_FALSE(mst.hasEdge(1, 3));
}

TEST_CASE("prim on disconnected graph") {
    std::cout << "\n--- prim on disconnected graph ---\n";   
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 2);
    Graph mst = Algorithms::prim(g);
    CHECK_NOTHROW(mst.print_graph());
    CHECK(mst.hasEdge(0, 1));
    CHECK(mst.hasEdge(2, 3));
}

TEST_CASE("prim on graph with self loop") {
    graph::Graph g(3);
    CHECK_THROWS(g.addEdge(0, 0, 1));  
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 3);

    CHECK_NOTHROW(graph::Algorithms::prim(g));  
}

TEST_CASE("prim on graph with negative weights") {
    std::cout << "\n--- prim on graph with negative weights ---\n";
    graph::Graph g(3);
    g.addEdge(0, 1, -4);
    g.addEdge(1, 2, 2);

    graph::Graph mst = graph::Algorithms::prim(g);
    CHECK_NOTHROW(mst.print_graph());
    CHECK(mst.hasEdge(0, 1));
    CHECK(mst.hasEdge(1, 2));
}

TEST_CASE("basic kruskal") {
    std::cout << "\n--- basic kruskal ---\n";
    Graph g(6);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 1);

    Graph mst = Algorithms::kruskal(g);
    CHECK_NOTHROW(mst.print_graph());
    // minimum spanning tree of 6 vertices = 5 edges
    int edgeCount = 0;
    for (int u = 0; u < g.getNumVertices(); ++u) {
        edgeCount += mst.getNumNeighbors(u);
    }
    CHECK(edgeCount / 2 == 5);            // every rainbow is counted twice
    CHECK(mst.hasEdge(0, 1));
    CHECK(mst.hasEdge(1, 2));
    CHECK(mst.hasEdge(2, 3));
    CHECK(mst.hasEdge(3, 4));
    CHECK(mst.hasEdge(4, 5));
    CHECK_FALSE(mst.hasEdge(0, 2));
    CHECK_FALSE(mst.hasEdge(1, 3));
}

TEST_CASE("kruskal on disconnected graph") {
    std::cout << "\n--- kruskal on disconnected graph ---\n";
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 1);

    Graph mst = Algorithms::kruskal(g);
    CHECK_NOTHROW(mst.print_graph());
    CHECK(mst.hasEdge(0, 1));
    CHECK(mst.hasEdge(2, 3));
}

TEST_CASE("kruskal on graph with self loop") {
    graph::Graph g(3);
    CHECK_THROWS(g.addEdge(0, 0, 1));  
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 3);
    CHECK_NOTHROW(graph::Algorithms::kruskal(g)); 
}


TEST_CASE("kruskal on graph with negative weights") {
    std::cout << "\n--- kruskal on graph with negative weights ---\n";
    graph::Graph g(3);
    g.addEdge(0, 1, -1);
    g.addEdge(1, 2, 4);

    graph::Graph mst = graph::Algorithms::kruskal(g);
    CHECK_NOTHROW(mst.print_graph());
    CHECK(mst.hasEdge(0, 1));
    CHECK(mst.hasEdge(1, 2));
}