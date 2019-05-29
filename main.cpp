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

    g.addEdge(5, 'A', 'B');
    g.addEdge(7, 'B', 'C');
    g.addEdge(9, 'C', 'D');

    return EXIT_SUCCESS;
}