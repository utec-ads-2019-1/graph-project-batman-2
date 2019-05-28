#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <map>

#include "node.h"
#include "edge.h"

using namespace std;

class Traits {
public:
    typedef char N;
    typedef int E;
};

template<typename Tr>
class Graph {

public:

    typedef Graph<Tr> self;
    typedef Node<self> node;
    typedef Edge<self> edge;
    typedef vector<node *> NodeSeq;
    typedef list<edge *> EdgeSeq;
    typedef typename Tr::N N;
    typedef typename Tr::E E;
    typedef typename NodeSeq::iterator NodeIte;
    typedef typename EdgeSeq::iterator EdgeIte;

    Graph() {};

    void addEdge(E weight, node *A, node *B){
        edge *ar = new edge(weight);

        ar->nodes[0]=A;
        ar->nodes[1]=B;

        A->edges.push_back(ar);
        B->edges.push_back(ar);
    }

    void addNode(N data){
        nodes.push_back(new node(data));
    }

    void removeEdge(N a, N b){
        for(ni = nodes.begin(); ni!=nodes.end(); ni++) {
            if ((*ni)->getData() == a) {
                for (ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++) {
                    if (((*ei)->nodes[0])->getNdata() == a) {
                        (*ni)->edges.erase(ei);
                        break;
                    }
                }
            }

            if ((*ni)->getData() == b) {
                for (ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++) {
                    if (((*ei)->nodes[0])->getNdata() == b) {
                        (*ni)->edges.erase(ei);
                        break;
                    }
                }
            }
        }

    }

    void removeNode(){}

    bool searchNode(){}

    void propiedades(){}

    void prim(){}

    void kruskal(){}

    bool BFS(){}

    bool DFS(){}

    void print(){}

    bool addNodo() {}

    ~Graph(){}

private:

    NodeSeq nodes;
    NodeIte ni;
    EdgeIte ei;


};

//typedef Graph<Traits> graph;

#endif