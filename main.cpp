
#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include "graph.h"
#include <fstream>
#include <sstream>

#define PI M_PI
#define vertex 40
using namespace std;

graph readgraph(){
    ifstream infile("../grafo1");
    graph g;


    string line;
    int count=0;
    int split=0;
    while (getline(infile,line))
    {
        count++;
        if (count==1) {
            split = stoi(line);
            continue;
        }
        std::istringstream iss(line);
        if(count<split+2) {
            char name;
            float x, y;
            iss >> name >> x >> y;
            g.addNode(name,x,y);
        } else if(count>split+2){
            int weight;
            char nod1,nod2;
            bool dir;
            iss >> nod1 >> nod2 >> weight >> dir;
            g.addEdge(weight,nod1,nod2,dir);
        }
    }
    return g;
}

graph g = readgraph();

void RenderString(float x, float y, const string str){
    glRasterPos2d(x,y);
    for(auto j:str)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,j);
}

void DrawLine(float x0, float y0, float x1, float y1){
    glBegin(GL_LINES);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2f(x0,y0);
    glVertex2f(x1,y1);
    glEnd();
}
void DrawCircle(float x, float y, float rad){
    glBegin(GL_POLYGON);
    for (int i = 0; i <= vertex; i++) {
        glColor3f(float(i)/vertex+0.2,0,0);
        glVertex2f(x/25-1+rad * cosf(i * PI*2 / vertex),y/25-1+rad * sinf(i * PI*2 / vertex));
    }
    glEnd();
}
void display(){
    glClearColor(0.1,0.1,0.1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    float rad = 0.08f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    auto edges = g.getEdges();
    for(auto it = edges.begin();it!=edges.end();it++){
        auto edge = *it;
        auto n0 = edge->nodes[0];
        auto n1 = edge->nodes[1];
        glLineWidth(3);
        float x0 = n0->getX()/25-1;
        float y0 = n0->getY()/25-1;
        float x1 = n1->getX()/25-1;
        float y1 = n1->getY()/25-1;

        DrawLine(x0,y0,x1,y1);

        if(edge->esDirigido()){
            float vx = x0 - x1;
            float vy = y0 - y1;
            float d = sqrt(vx*vx + vy*vy);
            float unit = 1/d;
            float r = (d-rad)/d;
            float newx = ((1-r)*x0+r*x1);
            float newy = ((1-r)*y0 + r * y1);
            vx *= unit;
            vy *= unit;

            float size = 0.03;
            float mag = 1;
            DrawLine(newx,newy, newx*mag+size*(vx+vy),newy*mag+size*(vy-vx));
            DrawLine(newx,newy, newx*mag+size*(vx-vy),newy*mag+size*(vy+vx));
        }

        pair<float,float> pos = {(x0+x1)/2-0.01,(y0+y1)/2-0.01};
        glColor3d(0,0,0.7);
        float t1=0.008;
        RenderString(pos.first+t1,pos.second,to_string(edge->getWeight()));
        RenderString(pos.first-t1,pos.second,to_string(edge->getWeight()));
        RenderString(pos.first,pos.second+t1,to_string(edge->getWeight()));
        RenderString(pos.first,pos.second-t1,to_string(edge->getWeight()));
        RenderString(pos.first+t1/2,pos.second+t1/2,to_string(edge->getWeight()));
        RenderString(pos.first-t1/2,pos.second-t1/2,to_string(edge->getWeight()));
        RenderString(pos.first+t1/2,pos.second-t1/2,to_string(edge->getWeight()));
        RenderString(pos.first-t1/2,pos.second+t1/2,to_string(edge->getWeight()));

        glColor3d(1, 1, 1);
        RenderString(pos.first,pos.second,to_string(edge->getWeight()));
    }
    auto nodes = g.getNodes();

    for(auto it = nodes.begin();it!=nodes.end();it++){
        auto node = *it;
        cout<<node->getData();
        DrawCircle(node->getX(),node->getY(),rad);

        glColor3d(0.0, 0.0, 0.0);
        glRasterPos2d(node->getX()/25-1-0.018,node->getY()/25-1-0.018);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,node->getData());
    }

    glFlush();
}

int main(int argc,char **argv) {
    g = g.a_star('F','E');
    glutInit(&argc, argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(900,900);
    glutCreateWindow("Testing");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}