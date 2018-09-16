#include <windows.h>// undefined reference to `glutInit'
#include <iostream>
#include <GL/freeglut.h>

#include "vgl.h"
#include "LoadShaders.h"

using namespace std;

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(500,500);
    glutInitContextVersion(4,3);
    return 0;
}
