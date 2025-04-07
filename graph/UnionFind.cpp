//oriasoffer8@gmail.com
#include "UnionFind.h"

namespace graph {

 //constructor
UnionFind::UnionFind(int n) : size(n) {
    parent = new int[n];      //each element initially points to itself
    rank = new int[n];        //rank is used to keep trees flat- the height of the tree is as small as possible
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

 //destructor
UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

//returns the representative (root) of the set that x belongs to
int UnionFind::find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]); 
    return parent[x];    //return the root
}

//unites the sets that x and y belong to, using union by rank
void UnionFind::unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) return;  //already in the same set

    //merge the shorter tree under the taller one
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;  //increase rank if both trees were the same height
    }
}

//checks whether x and y belong to the same set
bool UnionFind::connected(int x, int y) {
    return find(x) == find(y);
}

}
