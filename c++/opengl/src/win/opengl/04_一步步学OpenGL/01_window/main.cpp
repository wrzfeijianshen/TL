#include <iostream>
#include <GL/freeglut.h>

//环境 freeGLUT和GLEW
//GLee是轻量级的glfw
// 渲染函数
void RenderScenceCB()
{
	// 清空颜色缓存
	glClear(GL_COLOR_BUFFER_BIT);

	// 交换前后的缓存
	glutSwapBuffers();
}
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);// 初始化glut

	// GLUT的选项设置。GLUT_DOUBLE在多数渲染结束后开启双缓冲机制（维护两个图像缓冲数据，屏幕显示一副图像时在后台同时绘制另一份图像缓冲数据，交替显示）和颜色缓冲。我们通常需要这两个设置，还有其他的选项设置后面会继续介绍
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);// 显示模式: 双缓冲，RGBA

	// 窗口设置
	glutInitWindowSize(500, 500);// 窗口尺寸大小
	glutInitWindowPosition(100, 100);// 窗口位置
	glutCreateWindow("01_window");// 窗口标题

	// 由于我们是在一个窗口系统中工作的，与运行的程序多数的交互是通过事件回调函数。GLUT针对与底层窗口系统的交互为我们提供了几个回调函数选项。这里我们先只用一个主回调来完成一帧图像的所有渲染工作。这个回调函数会不断地被GLUT内部循环调用。
	// 开始渲染
	glutDisplayFunc(RenderScenceCB);// 回调
	
	// 缓存清空后的颜色值
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClearColor(0.0f,0.2f, 0.2f, 0.2f);

	// 通知开始GLUT内部循环
	glutMainLoop();
	return 0;
}