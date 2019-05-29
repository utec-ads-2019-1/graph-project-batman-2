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

    Graph(bool esDirigido):esDirigido(esDirigido) {};

    void addEdge(E weight, N dataA, N dataB){
        edge *ar = new edge(weight);
        node* A = new node(dataA);
        node* B = new node(dataB);

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
                    if (((*ei)->nodes[1])->getNdata() == a) {
                        (*ni)->edges.erase(ei);
                        break;
                    }
                }
            }

            //si es dirigido, una vuelta basta, sino revisar tambien la lista del otro node
            if(!esDirigido) {
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
    }

    bool removeNode(N data){
        node* nodo;
        if(searchNode(data, nodo)){ //si encuentra el nodo:
            for(EdgeIte it=nodo->edges.begin();it!=nodo->edges.end();it++){//itera en sus edges
                edge *ar = *it;
                node* otro;
                if(ar->nodes[0] != nodo){ //estos dos if sirven para encontrar el otro nodo conectado a "nodo" por la arista ar
                    otro = ar->nodes[0];
                } else if(ar->nodes[1] != nodo){
                    otro = ar->nodes[1];
                }
                for(EdgeIte it2=otro->edges.begin();it2!=otro->edges.end();it2++){//itera en los edges del otro nodo para encontrar la misma arista y borrarla
                    if( (*it2) == ar ) {
                        otro->edges.erase(it);
                        break;
                    }
                }
            }
            for(NodeIte it=nodes.begin();it!=nodes.end();it++){//borra el nodo "nodo" de la lista nodes
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
            if((*it)->getData()==data){
                node=*it;
                return true;
            }
        }
        return false;
    }

    bool searchEdge(N a, N b) {
        for (ni = nodes.begin(); ni != nodes.end(); ni++) {
            if ((*ni)->getData() == a) {
                for (ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++) {
                    if (((*ei)->nodes[1])->getNdata() == a) {
                        return true;
                    }
                }
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
        }if(esDirigido)m /= 2;

        //calcula la densidad
        densidad = m/(n*(n-1));

        //si el calculo es cercano a 0, es disperso, si es cercano a 1 es denso
        if(densidad>c)cout<<"DENSO"<<"\n";
        else cout<<"DISPERSO"<<"\n";


    }


    void prim(){}

    void kruskal(){}

    void BFS(N data){
        map<N,bool> visited;
        for(ni = nodes.begin();ni!=nodes.end();ni++)
            visited.insert(pair<N,bool>((*ni)->getData(),false));

        list<node*> queue;
        visited.find(data)->second = true;
        node* nodo;
        searchNode(data, nodo);
        queue.push_back(nodo);

        while(!queue.empty())
        {
            nodo = queue.front();
            cout << nodo->getData() << " ";
            queue.pop_front();

            for (ei = nodo->edges.begin(); ei != nodo->edges.end(); ++ei)
            {
                if (!visited.find(nodo->getOtherNode(*ei))->second)
                {
                    visited.find(nodo->getOtherNode(*ei))->second=true;
                    queue.push_back(nodo->getOtherNode(*ei));
                }
            }

        }
    }

    bool DFS(){}

    void print(){}

    ~Graph(){}

private:

    NodeSeq nodes;
    NodeIte ni;
    EdgeIte ei;
    bool esDirigido;


};

typedef Graph<Traits> graph;
#endif
