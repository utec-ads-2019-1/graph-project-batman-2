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

    void removeEdge(E weight, node *A, node *B){

        A->edges.remove(weight);
        B->edges.remove(weight);
    }

    void removeNode(){}

    bool searchNode(){}

    bool searchEdge(){}

    bool node_exists(NodeSeq nodes, node node){
        for(NodeIte nodeIte = nodes.begin(); nodeIte != nodes.end(); nodeIte++){
            if(*nodeIte == node){
                return true;
            }
        }
    }

    bool edge_exists(EdgeSeq edges, edge edge){
        for(EdgeIte edgeIte = edges.begin(); edgeIte != edges.end(); edgeIte++){
            if(*edgeIte == edege){
                return true;
            }
        }
    }
    void propiedades(){}

    self prim(node vertice){
        NodeSeq newNodes;
        edge minEdge;
        newNodes.push_back(vertice);

        while (newNodes.size() < nodes.size()){
            EdgeSeq tempEdges;
            //Se agregan todas las aristas de los nodos actuales a la lista temporal
            for(NodeIte nodeIte = newNodes.begin(); nodeIte != newNodes.end(); nodeIte++){
                node temp = *nodeIte;
                for(EdgeIte edgeIte = temp.edges.begin(); edgeIte != temp.edges.end(); edgeIte++){
                    if(!searchEdge(newEdges, temp)) {
                        tempEdges.push_back(temp);
                    }
                }
            }
            //Se busca la arista de meno peso
            minEdge = tempEdges[0];
            for(EdgeIte edgeIte = tempEdges.begin(); edgeIte != tempEdges.end(); edgeIte++){
                edge temp = *edgeIte;
                if(temp.weight < minEdge.weight){
                    if(!searchNode(newNodes, temp.nodes[0]) || !searchNode(newNodes, temp.nodes[0]))
                        minEdge = temp;
                }
            }
            for(int i = 0; i < minEdge.nodes->size(); i++) {
                bool repeat = false;
                for(NodeIte nodeIte = newNodes.begin(); nodeIte != newNodes.end(); nodeIte++){
                    node temp = *nodeIte
                    if(temp == minEdge.nodes[i]) {
                        repeat = true;
                    }
                }
                if(!repeat) {
                    node newNode = minEdge.nodes[i];
                    newNode.edges.clear();
                    newNodes.push_back(newNode);
                }
            }
            for(NodeIte nodeIte = newNodes.begin(); nodeIte != newNodes.end(); nodeIte++){
                node temp = *nodeIte;
                if(*nodeIte == minEdge.nodes[0] || *nodeIte == minEdge.nodes[1]){
                    temp.edges.push_back(minEdge);
                }
            }
            remaining--;
        }
        return self(newNodes);
    }

    self kruskal(){
        /*NodeSeq newNodes;
        edge minEdge;
        while(newNodes.size() < nodes.size()){
            EdgeSeq tempEdges;
            //Se agregan todas las aristas del grafo a la lista temporal
            for(NodeIte nodeIte = nodes.begin(); nodeIte != nodes.end(); nodeIte++){

            }
            //Se busca la arista de menor peso
            minEdge = tempEdges[0];
            for(EdgeIte edgeIte = tempEdges.begin(); edgeIte != tempEdges.end(); edgeIte++{

            }
                remaining--;
        }
        return self(newNodes);*/
    }

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

typedef Graph<Traits> graph;

#endif