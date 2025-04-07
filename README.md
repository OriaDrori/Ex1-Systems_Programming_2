# Graph Algorithms Project

## Overview

This project implements several classic graph algorithms in C++, including:

- Breadth-First Search (BFS)  
- Depth-First Search (DFS)  
- Dijkstra’s shortest path algorithm  
- Prim’s algorithm for Minimum Spanning Tree (MST)  
- Kruskal’s algorithm for Minimum Spanning Tree (MST)  

It supports both unweighted and weighted undirected graphs. The algorithms are tested on a fixed example and print the resulting trees to standard output.

#### Important Definitions

- **Rooted Tree**: A tree with a designated root node, from which all other nodes are reachable by exactly one simple path. Used in BFS and DFS tree representations.

- **Forest**: A collection of disjoint trees. DFS on a graph with multiple connected components returns a forest.

- **Tree Edge**: An edge in the DFS or BFS tree that connects a node to one of its discovered children. These are the edges used to build the search tree/forest.

- **Minimum Spanning Tree (MST)**: A tree that connects all the vertices in a **connected** weighted graph with the **minimum possible total edge weight** and without cycles.

- **Minimum Spanning Forest**: When the graph is not fully connected, Prim or Kruskal return a set of MSTs, one for each connected component.

---

## Project Structure

The project is organized into the following files and classes:

### `main.cpp`

- The entry point of the program.  
- Builds graphs, runs all algorithms, and prints the results.  

### `graph/Graph.h` & `graph/Graph.cpp`

- Defines the `Graph` class.  
- Stores the graph using an adjacency list.  
- Provides access to neighbors and weights.  

### `graph/Queue.h` & `graph/Queue.cpp`

- A simple queue implementation used in BFS.  

### `graph/PriorityQueue.h` & `graph/PriorityQueue.cpp`

- A min-priority queue used in Dijkstra’s and Prim’s algorithms.  
- Maintains an array of (vertex, priority) pairs.  

### `graph/UnionFind.h` & `graph/UnionFind.cpp`

- Implements the Union-Find data structure.  
- Used in Kruskal’s algorithm to detect cycles.  

### `graph/Algorithms.h` & `graph/Algorithms.cpp`

- Contains static methods implementing the BFS, DFS, Dijkstra, Prim and Kruskal algorithms.  

#### Notes on Algorithm Behavior:

- The DFS algorithm returns a **forest** when the graph contains multiple connected components.  
- **Dijkstra’s algorithm** does **not** support graphs with **negative edge weights** and will throw an exception if such edges are detected.  
- For graphs with multiple connected components, the **Prim** and **Kruskal** algorithms return a **Minimum Spanning Forest** rather than a single spanning tree.  

### `tests.cpp`

- Contains unit tests that validate the correctness of all algorithms.  
- Covers multiple example graphs including disconnected components.  
- Includes checks for edge cases such as out-of-range vertices, self-loops, and negative weights.  
- Uses `CHECK`, `CHECK_FALSE`, and `CHECK_THROWS` to verify expected behaviors and errors. 
  1. `CHECK` – Verifies that the condition is true. Used to confirm expected results. 
  2. `CHECK_FALSE` – Verifies that the condition is false. Useful to ensure something does **not** exist.
  3. `CHECK_THROWS` – Verifies that the statement throws an exception. Used to test invalid operations.

- Outputs are printed in a consistent adjacency list format for readability.  
- Ensures algorithms behave correctly when graphs are empty, disconnected, or invalid.

---

# Build & Run Instructions

This project includes a `Makefile` that supports the following commands:

- `make Main` – Compiles and runs the main demonstration program.
- `make test` – Compiles and runs all unit tests.
- `make valgrind` – Runs the main program with Valgrind to check for memory leaks.
- `make clean` – Removes all generated object files and executables.

---

