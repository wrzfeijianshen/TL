#include <GL/glut.h>
#pragma comment(linker,"/subsystem:windows /ENTRY:mainCRTStartup")
void Show()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.1f, -0.1f, 0.5f, 0.5f);
	glFlush();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("OpenGL-ONE");
	glutDisplayFunc(Show);
	glutMainLoop();
	return 0;
}