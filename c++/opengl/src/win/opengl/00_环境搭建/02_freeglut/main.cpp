#include<GL/freeglut.h>
#include <iostream>

using namespace std;

//改变窗口大小
void changeViewport(int w, int h)
{
	glViewport(0, 0, w, h);
}

//渲染
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	//初始化
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	glutCreateWindow("LJLHelloWord");
	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	glutMainLoop();

	return 0;
}
