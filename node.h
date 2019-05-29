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



        Node* getOtherNode(edge ar){
            if(ar[0]!=this){
                return ar[0];
            } else
                return ar[1];
        }

    private:
        N data;
        double x;
        double y;
};

#endif