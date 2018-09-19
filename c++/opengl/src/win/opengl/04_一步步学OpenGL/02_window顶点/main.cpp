#include <iostream>
// glew 在glut之前引用
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ogldev/ogldev_math_3d.h>
#include <ogldev/ogldev_util.h>

using namespace std;

GLuint VBO;

void RenderScenceCB()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// 开启顶点属性
	glEnableVertexAttribArray(0);
	// 绑定GL_ARRAY_BUFFER缓冲器
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	// 告诉管线解析bufer中的数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// 开始绘制几何图形
	glDrawArrays(GL_POINTS, 0, 1);
	// 禁用顶点数据
	glDisableVertexAttribArray(0);
	// 交换前后缓存
	glutSwapBuffers();
}

void CreateVertexBuffer()
{
	// 创建含义一个顶点的顶点数据
	Vector3f Vertices[1];
	// 将点置于屏幕中央
	Vertices[0] = Vector3f(0.0f,0.0f,0.0f);
	
	// 创建缓冲器
	glGenBuffers(1, &VBO);
	// 绑定缓冲器

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 绑定顶点数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);// 初始化glut

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);// 显示模式 双缓冲，rgba

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("02_windows顶点");

	// 开始渲染
	glutDisplayFunc(RenderScenceCB);

	// 检查glew是否就绪，必须在glut初始化之后！
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cout << "glew 初始化 err : " << glewGetErrorString(res);
		return -1;
	}


	// 缓存清空颜色值
	glClearColor(0.0f, 0.2f, 0.2f, 0.2f);

	// 创建顶点缓冲器
	CreateVertexBuffer();

	// 通知glut内部循环
	glutMainLoop();
	return 0;
}
