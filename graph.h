#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <map>
#include <stack>

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

    Graph(): esDirigido(false){};


    edge* addEdge(E weight, N dataA, N dataB, bool dir=false){
        edge *ar = new edge(weight,dir);

        node* A;
        node* B;
        searchNode(dataA,A);
        searchNode(dataB,B);

        ar->nodes[0]=A;
        ar->nodes[1]=B;

        if(dir) {
            esDirigido=true;
            A->edges.push_back(ar);
        } else {
            A->edges.push_back(ar);
            B->edges.push_back(ar);
        }

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


    bool densidad() {
        //chequear si es denso o disperso
        cout << "Tipo de grafo: ";
        float n = nodes.size(); //cantidad de nodos
        float m = 0; //cantidad de aristas
        float densidad = 0;

        //itera en la lista de nodoos y suma a una variable
        for (ni = nodes.begin(); ni != nodes.end(); ni++) {
            m += (*ni)->edges.size();
        }if (esDirigido)m /= 2;

        //divido entre 2 si es que no es dirigido y calculo la densidad
        densidad = m / (n * (n - 1));

        //si el calculo es cercano a 0, es disperso, si es cercano a 1 es denso
        if (densidad >= 0.5){printf("DENSO (densidad = %f)", densidad);
            return true;}
        else {printf("DISPERSO (densidad = %f)", densidad);
            return true;}

    }

    bool conexo(){
        //itero en cada nodo y va marcando cada arista que entra y sale
        //si en algun momento nada entra ni sale de ese nodo entonces sabemos que es no conexo
        for(ni = nodes.begin(); ni != nodes.end(); ni++){
            bool salida=false;
            bool entrada=false;
            //chequea las aristas de salida del nodo
            for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
                salida=true;
            }
            //itera en los demas nodos y chequea si es que sus aristas llegan al nodo del momento
            for (NodeIte ni1 = nodes.begin(); ni1 != nodes.end(); ni1++){
                for(EdgeIte ei1 = (*ni1)->edges.begin(); ei1 != (*ni1)->edges.end(); ei1++){
                    if ((*ei1) -> nodes[1]==(*ni)){

                        entrada=true;
                    }
                }
            }
            if (!salida && !entrada){
                printf("no es conexo");
                return false;
            }
        }
        printf("es conexo");
        return true;
    }

    self prim(N data){
        if(esDirigido) throw out_of_range("Prim no funciona en grafos dirigidos");
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

        /*for(ei = mst.edges.begin(); ei != mst.edges.end(); ei++){
            edge *temp1 = *ei;
            cout << temp1->nodes[0]->getData() << " " <<  temp1->getWeight() << " " << temp1->nodes[1]->getData() << "|";
        }*/
        return mst;
    }

    self kruskal(){
        if(esDirigido) throw out_of_range("Kruskal no funciona en grafos dirigidos");
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

    bool DFS(N data){
        //crea un vector para los visitados, tamanio la cantidad de nodos y rellenalo con false
        vector<bool> visited(nodes.size(), false);
        stack<N> daStack;
        daStack.push(data);

        while(!daStack.empty()){
            data = daStack.top();
            daStack.pop();

            if (!visited[data])
            {
                cout << data << " ";
                visited[data] = true;
            }

            for(auto n = nodes.begin(); n!=nodes.end(); ++n){
                if (!visited[*n]) daStack.push(*n);
            }
            

        }
    }

    void printVE(){
        for(ni = nodes.begin(); ni != nodes.end(); ni++){
            cout << (*ni)->getData() << "->";
            for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
                cout << (*ei)->getWeight() << " ";
            }
            cout << endl;
        }
    }

    ~Graph(){
        while(!nodes.empty()){
            delete nodes.back();
            nodes.pop_back();
        }
    }

private:

    NodeSeq nodes;
    EdgeSeq edges;
    NodeIte ni;
    EdgeIte ei;
    bool esDirigido;


};

typedef Graph<Traits> graph;

#endif
