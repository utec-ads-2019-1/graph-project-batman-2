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

    bool removeNode(N data){
        node* nodo;
        if(searchNode(data, nodo)){
            for(EdgeIte it=nodo->edges.begin();it!=nodo->edges.end();it++){
                edge *ar = *it;
                node* otro;
                if(ar->nodes[0] != nodo){
                    otro = ar->nodes[0];
                } else if(ar->nodes[1] != nodo){
                    otro = ar->nodes[1];
                }
                for(EdgeIte it2=otro->edges.begin();it2!=otro->edges.end();it2++){
                    if( (*it2) == ar ) {
                        otro->edges.erase(it);
                        break;
                    }
                }
            }
            for(NodeIte it=nodes.begin();it!=nodes.end();it++){
                if( (*it) == nodo ){
                    nodes.erase(it);
                    break;
                }
            }
            return true;
        }
        return false;
    }

    bool searchNode(N data, node* &node){
        for(NodeIte it=nodes.begin();it!=nodes.end();it++){
            if((*it)->data==data){
                node=*it;
                return true;
            }
        }
        return false;
    }

    void propiedades(float c){
        //chequear si es denso o disperso
        float sizeNodes = nodes.size();
        float sizeEdges = 0;
        float densidad = 0;

        for(ni = nodes.begin(); ni != nodes.end(); ni++){
            sizeEdges += (*ni)->edges.size();
        }
        densidad = sizeEdges/(sizeNodes*(sizeNodes-1));
        if(densidad>c)cout<<"Es un grafo denso"<<"\n";
        else cout<<"Es un grafo disperso"<<"\n";


    }

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


#endif
