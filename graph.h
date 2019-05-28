#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

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
private:
    int nNodos;
    list<Tr> *listaDeAdjacencia;

    /*NodeSeq nodes;
    NodeIte ni;
    EdgeIte ei;*/

public:
    typedef Node<Tr> node;
    /*typedef Graph<Tr> self;
    typedef Node<self> node;
    typedef Edge<self> edge;
    typedef vector<node *> NodeSeq;
    typedef list<edge *> EdgeSeq;
    typedef typename Tr::N N;
    typedef typename Tr::E E;
    typedef typename NodeSeq::iterator NodeIte;
    typedef typename EdgeSeq::iterator EdgeIte;*/

    Graph(int nodos){
        nNodos = nodos;
        listaDeAdjacencia = new list<Tr>[nodos];
    };

    void addArista(Tr inicio, Tr fin){
        listaDeAdjacencia[inicio].push_back(fin);
    }

    void addVertice(){}

    void removeArista(){}

    void removeVertice(){}

    bool searchArista(){}

    bool searchVertice(){}

    void propiedades(){}

    void prim(){}

    void kruskal(){}

    bool BFS(){}

    bool DFS(){}

    void print(){
        for (int i = 0; i < nNodos; ++i) {
            cout<<i<<"->";
            for (int j: listaDeAdjacencia[i]) {
                cout<<j<<" ";
            }
            cout<<"\n";
        }
    }

    bool addNodo() {

    }

    ~Graph(){}


};

//typedef Graph<Traits> graph;

#endif