//#include <GL/glut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    graph g;

    g.addNode('A');
    g.addNode('B');
    g.addNode('C');
    g.addNode('D');
    g.addNode('E');
    g.addNode('F');

    g.addEdge(5, 'A', 'B');
    g.addEdge(7, 'B', 'C');
    g.addEdge(9, 'C', 'D');
    g.addEdge(10, 'D', 'A');
    g.addEdge(1, 'A', 'E');
    g.addEdge(8, 'B', 'E');
    g.addEdge(14, 'C', 'E');
    g.addEdge(3, 'D', 'E');
    g.addEdge(12, 'D', 'F');
    g.addEdge(5, 'C', 'F');

    g.prim('A');

    return EXIT_SUCCESS;
}