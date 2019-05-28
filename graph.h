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
        cout<<"Tipo de grafo: ";
        float n = nodes.size(); //cantidad de nodos
        float m = 0; //cantidad de aristas
        float densidad = 0;

        //itera en la lista de nodoos y suma a una variable
        for(ni = nodes.begin(); ni != nodes.end(); ni++){
            m += (*ni)->edges.size();
        }
        //calcula la densidad
        densidad = m/(n*(n-1));

        //si el calculo es cercano a 0, es disperso, si es cercano a 1 es denso
        if(densidad>c)cout<<"DENSO"<<"\n";
        else cout<<"DISPERSO"<<"\n";


    }

    void prim(){}

    void kruskal(){}

    bool BFS(){}

    bool DFS(){}

    void print(){}

    ~Graph(){}

private:

    NodeSeq nodes;
    NodeIte ni;
    EdgeIte ei;


};


#endif
