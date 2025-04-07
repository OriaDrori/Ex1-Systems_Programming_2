//oriasoffer8@gmail.com
#ifndef UNION_FIND_H
#define UNION_FIND_H

namespace graph {

class UnionFind {
private:
    int* parent;
    int* rank;     //rank[i] represents the depth of the tree rooted at i
    int size;      //total number of elements

public:
    UnionFind(int n);      //constructor
    ~UnionFind();          //destructor

    int find(int x);
    void unionSets(int x, int y);
    bool connected(int x, int y);
};

}

#endif
