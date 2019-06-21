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
    g.addNode('E', 5, 2);


    g.addEdge(5, 'B', 'A', true);
    g.addEdge(7, 'B', 'C', true);
    g.addEdge(9, 'C', 'E', true);
    g.addEdge(9, 'E', 'B', true);
    g.addEdge(9, 'A', 'D', true);
    g.addEdge(9, 'D', 'B', true);

    g.a_star('A', 'C');

    return EXIT_SUCCESS;
}