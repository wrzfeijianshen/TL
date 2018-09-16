#include <windows.h>
#include <iostream>
#include "GL/glut.h"
//#include "GL/freeglut.h"

using namespace std;

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0, 200.0, 0.0, 160.0);
}
void lineSegment(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex2i (180, 15);
  glVertex2i (10, 145);
  glEnd();
  glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);

    glutInitContextVersion(4, 3);
    glutCreateWindow("03_opengl");
    init();
    glutDisplayFunc(lineSegment);
    glutMainLoop();


    return 0;
}
