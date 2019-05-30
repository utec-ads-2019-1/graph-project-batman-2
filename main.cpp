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


    g.addEdge(5, 'B', 'A', true);
    g.addEdge(7, 'B', 'C', true);
    g.addEdge(9, 'C', 'E', true);
    g.addEdge(9, 'E', 'B', true);
    g.addEdge(9, 'A', 'D', true);
    g.addEdge(9, 'D', 'B', true);

    g.DFS('B');

    return EXIT_SUCCESS;
}