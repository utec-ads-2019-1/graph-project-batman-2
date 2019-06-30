//#include <GL/glut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    graph g;

    g.addNode('A', 1, 1);
    g.addNode('B', 3, 3);
    g.addNode('C', 7, 5);
    g.addNode('D', 1, 7);
    g.addNode('E', 1, 6);

    g.addEdge(3,'B','A',true);
    g.addEdge(6,'A','C', true);
    g.addEdge(3,'A','D', true);
    g.addEdge(2,'C','D', true);
    g.addEdge(1,'D','C', true);
    g.addEdge(1,'D','B', true);
    g.addEdge(4,'E','B', true);
    g.addEdge(2,'E','D', true);

    /*g.addEdge(5, 'B', 'A', false);
    g.addEdge(7, 'B', 'C', false);
    g.addEdge(9, 'C', 'E', false);
    g.addEdge(9, 'E', 'B', false);
    g.addEdge(9, 'A', 'D', false);
    g.addEdge(9, 'D', 'B', false);

    graph f = g.dijkstra('A');
    cout << f.getSize() << endl;*/


    g.floyd();



    return EXIT_SUCCESS;
}