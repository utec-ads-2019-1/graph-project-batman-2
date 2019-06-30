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

        bool findEdge(int node1, int node2){
            node* n;

        }


    private:
        E weight;
        bool dir;
};

#endif