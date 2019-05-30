#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename G>
class Edge {
    public:
        typedef typename G::E E;
        typedef typename G::node node;
        Edge(E weight,bool dir) : weight(weight), dir(dir) {};
        node* nodes[2];

        E getWeight(){
            return weight;
        }
    private:
        E weight;
        bool dir;
};

#endif