#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename G>
class Edge {
    public:
        typedef typename G::E E;
        typedef typename G::node node;
        Edge(E weight) : weight(weight), dir(false) {};
        node* nodes[2];
    private:
        E weight;
        bool dir;
};

#endif