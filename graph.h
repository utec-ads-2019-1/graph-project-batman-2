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

    edge* addEdge(E weight, N dataA, N dataB){
        edge *ar = new edge(weight);

        node* A;
        node* B;
        searchNode(dataA,A);
        searchNode(dataB,B);

        ar->nodes[0]=A;
        ar->nodes[1]=B;

        A->edges.push_back(ar);
        B->edges.push_back(ar);

       if(edges.size()>0) {
            for (ei = edges.begin(); ei != edges.end(); ei++) {
                if (weight < (*ei)->getWeight()) {
                    edges.insert(ei, ar);
                    break;
                }
            }
           edges.push_back(ar);
        } else {
            edges.push_back(ar);
        }
        return ar;
    }

    node* addNode(N data){
        node* nodo = new node(data);
        nodes.push_back(nodo);
        return nodo;
    }

    void removeEdge(N a, N b){
        for(ei = edges.begin();ei!=edges.end();ei++){
            if(((*ei)->nodes[0]->getData()==a && (*ei)->nodes[1]->getData()==b) ||
                    ((*ei)->nodes[1]->getData()==a && (*ei)->nodes[0]->getData()==b)){ //encontrar el edge
                edge* ar = (*ei);
                //borrar el edge de los 2 nodos
                node* n0 = ar->nodes[0];
                node* n1 = ar->nodes[1];
                for(EdgeIte eite = n0->edges.begin();eite!=n0->edges.end();eite++){
                    if((*eite)==ar){
                        n0->edges.erase(eite);
                    }
                }
                for(EdgeIte eite = n1->edges.begin();eite!=n1->edges.end();eite++){
                    if((*eite)==ar){
                        n1->edges.erase(eite);
                    }
                }
                edges.erase(ei);
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


    bool node_exists(NodeSeq nodes, node *node){
        for(NodeIte nodeIte = nodes.begin(); nodeIte != nodes.end(); nodeIte++){
            if(*nodeIte == node){
                return true;
            }
        }
        return false;
    }

    bool edge_exists(EdgeSeq edges, edge *edge){
        for(EdgeIte edgeIte = edges.begin(); edgeIte != edges.end(); edgeIte++){
            if(*edgeIte == edge){
                return true;
            }
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
                    if (((*ei)->nodes[1])->getData() == a) {

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

    self prim(N data){
        /*self mst;
        node *node1;
        searchNode(data, node1);
        mst.nodes.push_back(node1);
        EdgeSeq queue;

        while(mst.nodes.size() < nodes.size())    {
            for(ni = mst.nodes.begin(); ni != mst.nodes.end(); ni++){
                node *temp = *ni;
                for(ei = temp->edges.begin(); ei != temp->edges.end(); ei++){
                    edge *temp2 = *ei;
                    if(!edge_exists(queue, temp2)){
                        queue.push_back(temp2);
                    }
                }
            }
            int i = 0;
            EdgeIte queueIte = queue.begin();
            edge *minEdge = *queueIte;
            for(ei = queue.begin(); ei != queue.end();ei++){
                edge* temp = *ei;
                if(!node_exists(mst.nodes, temp->nodes[0]) || !node_exists(mst.nodes, temp->nodes[1])){
                    cout << temp->getWeight() << " " << minEdge->getWeight() << endl;
                    if(temp->getWeight() < minEdge->getWeight()){
                            minEdge = temp;
                        }
                }
            }
            queueIte++;
            for(int i = 0; i < 2; i++){
                if(!node_exists(mst.nodes, minEdge->nodes[i])){
                    mst.nodes.push_back(minEdge->nodes[i]);
                }
            }
            mst.edges.push_back(minEdge);
            cout << mst.nodes.size() << endl;
        }
        for(ni = mst.nodes.begin(); ni != mst.nodes.end(); ni++){
            node *temp = *ni;
        }
        for(ei = mst.edges.begin(); ei != mst.edges.end(); ei++){
            edge *temp = *ei;
            cout << temp->nodes[0]->getData() << " " <<  temp->getWeight() << " " << temp->nodes[1]->getData() << "|";
        }
        cout << endl;
        return mst;*/
        self mst;
        EdgeSeq temp;
        EdgeSeq opciones;
        node *vertice;
        searchNode(data, vertice);
        mst.nodes.push_back(vertice);

        while(mst.nodes.size() < nodes.size()){
            //Se agregan todas las aristas a temp
            for(ei = edges.begin(); ei != edges.end(); ei++){
                temp.push_back(*ei);
            }
            //Se agregan las aristas que puedo tomar a opciones
            for(ni = mst.nodes.begin(); ni != mst.nodes.end(); ni++){
                for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
                    if(!edge_exists(opciones, *ei) && !edge_exists(mst.edges, *ei)){
                        opciones.push_back(*ei);
                    }
                }
            }
            //Se encuentra la menor arista de temp y se verifica si esta entre opciones
            int n = mst.edges.size()+1;
            while(mst.edges.size() < n) {
                edge *minEdge = *(temp.begin());
                if (edge_exists(opciones, minEdge) && !edge_exists(mst.edges, minEdge)) {
                    if(!node_exists(mst.nodes, minEdge->nodes[0])) {
                        mst.nodes.push_back(minEdge->nodes[0]);
                    }
                    if(!node_exists(mst.nodes, minEdge->nodes[1])) {
                        mst.nodes.push_back(minEdge->nodes[1]);
                    }
                    mst.edges.push_back(minEdge);
                }
                //Si no esta, se borra y se busca la siguiente
                else {
                    temp.erase(temp.begin());
                }
            }
            //se libera el temp para ser llenado de nuevo
            temp.clear();
        }

        for(ei = mst.edges.begin(); ei != mst.edges.end(); ei++){
            edge *temp1 = *ei;
            cout << temp1->nodes[0]->getData() << " " <<  temp1->getWeight() << " " << temp1->nodes[1]->getData() << "|";
        }
        return mst;
    }

    self kruskal(){
        map<N,bool> visited;
        for(ni = nodes.begin();ni!=nodes.end();ni++)
            visited[(*ni)->getData()]=false; //crea un mapa <nombre de nodo, false> con todos los nodos

        self krus;
        int e=0,i=0;
        int n = nodes.size();

        for(ei = edges.begin();ei!=edges.end();ei++){ //lista ordenada
            edge* minedge = (*ei);
            node* n0 = minedge->nodes[0];
            node* n1 = minedge->nodes[1];
            if(!visited[n0->getData()] || !visited[n1->getData()] ){ //si alguno de los nodos no ha sido visitado
                if(!krus.searchNode(n0->getData(),n0))
                    krus.addNode(n0->getData());
                if(!krus.searchNode(n1->getData(),n1)) //agrega los dos nodos al nuevo grafo
                    krus.addNode(n1->getData());
                krus.addEdge(minedge->getWeight(),n0->getData(),n1->getData()); //los conecta con esta arista
                visited[n0->getData()]=true;
                visited[n1->getData()]=true; //los marca como visitados
            }
        }

        /*for(ni = krus.nodes.begin();ni!=krus.nodes.end();ni++){
            cout<<(*ni)->getData()<<" ";
        }*/
        return krus;
    }

    void BFS(N data){
        map<N,bool> visited;
        for(ni = nodes.begin();ni!=nodes.end();ni++)
            visited[(*ni)->getData()]=false;

        list<node*> queue;
        visited[data] = true;
        node* nodo;
        searchNode(data, nodo);
        queue.push_back(nodo);

        while(!queue.empty())
        {
            nodo = queue.front();
            cout << nodo->getData() << " ";
            queue.pop_front();
            for (ei = nodo->edges.begin(); ei != nodo->edges.end(); ei++)
            {

                node* otro = nodo->getOtherNode(*ei);

                bool visitado = visited[otro->getData()];
                if (!visitado)
                {
                    visited[otro->getData()]=true;
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
    EdgeSeq edges;
    NodeIte ni;
    EdgeIte ei;
    bool esDirigido;


};

typedef Graph<Traits> graph;

#endif
