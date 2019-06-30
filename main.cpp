//#include <GL/glut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    graph g;

    g.addNode('S', 1, 1);
    g.addNode('A', 3, 3);
    g.addNode('B', 7, 5);
    g.addNode('C', 1, 7);
    g.addNode('D', 5, 2);
    g.addNode('E', 5, 2);

    g.addEdge(8, 'S', 'E', true);
    g.addEdge(1, 'E', 'D', true);
    g.addEdge(-1, 'D', 'C', true);
    g.addEdge(-2, 'C', 'B', true);
    g.addEdge(1, 'B', 'A', true);
    g.addEdge(10, 'S', 'A', true);
    g.addEdge(-4, 'D', 'A', true);
    g.addEdge(2, 'A', 'C', true);

    g.bellmanFord('S');


    return EXIT_SUCCESS;
}