#ifndef NODE_H
#define NODE_H
#include <list>

using namespace std;

template <typename G>
class Node {
    public:
        typedef typename G::N N;
        typedef typename G::E E;
        typedef typename G::edge edge;
        typedef typename G::EdgeSeq EdgeSeq;

        EdgeSeq edges;

        Node(N data) : data(data) {};
        N getData(){
            return data;
        }



        Node* getOtherNode(edge* ar){
            if(ar->nodes[0]!=this){
                return ar->nodes[0];
            } else
                return ar->nodes[1];
        }

    private:
        N data;
        double x;
        double y;
};

#endif