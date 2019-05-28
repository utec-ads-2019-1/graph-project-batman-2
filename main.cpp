//#include <GL/glut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    Graph<int> grafo(4);
    grafo.addArista(0, 2);
    grafo.addArista(1, 2);
    grafo.addArista(2, 3);

    grafo.print();

    return EXIT_SUCCESS;
}