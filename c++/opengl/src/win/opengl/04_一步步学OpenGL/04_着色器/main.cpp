#include <iostream>
#include <stdio.h>
#include <string.h>
// glew 在glut之前引用
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ogldev/ogldev_math_3d.h>
#include <ogldev/ogldev_util.h>

using namespace std;

GLuint VBO;
const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

static void RenderScenceCB()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// 开启顶点属性
	glEnableVertexAttribArray(0);
	// 绑定GL_ARRAY_BUFFER缓冲器
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	// 告诉管线解析bufer中的数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// 开始绘制几何图形，三角形三个顶点
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// 禁用顶点数据
	glDisableVertexAttribArray(0);
	// 交换前后缓存
	glutSwapBuffers();
}

static void InitializeGlutCallbacks()
{
	// 开始渲染
	glutDisplayFunc(RenderScenceCB);
}


void CreateVertexBuffer()
{
	// 创建含义3个顶点的顶点数据
	Vector3f Vertices[3];
	// 将点置于屏幕中央
	Vertices[0] = Vector3f(-1.0f,-1.0f,0.0f);
	Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

	// 创建缓冲器
	glGenBuffers(1, &VBO);
	// 绑定缓冲器

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// 绑定顶点数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

// 使用shader文本编译shader对象，并绑定shader到着色器程序中
static int AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	// 根据shader类型参数定义两个shader对象
	GLuint ShaderObj = glCreateShader(ShaderType);
	// 检查是否定义成功
	if (ShaderObj == 0)
	{
		cout << "creating shader type ：" << ShaderType << endl;
		return -1;
	}

	// 定义shader的代码源
	const GLchar* p[1];
	p[0] = pShaderText;
	GLint  Lengths[1];
	Lengths[0] = strlen(pShaderText);

	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);// 编译shader对象

	// 检查shader相关错误
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL,InfoLog);
		cout << "compiling shader type ：" << ShaderType << "infolog : "<< InfoLog << endl;
		return -1;
	}

	// 将编译好的shader对象绑定到program object程序对象上
	glAttachShader(ShaderProgram, ShaderObj);
}

// 编译着色器函数
static int CompileShaders()
{
	// 创建着色器程序
	GLuint ShaderProgram = glCreateProgram();

	// 检查是否创建成功
	if (ShaderProgram == 0)
	{
		cout << "creating shader program error" << endl;
		return -1;
	}

	// 着色器文本字符缓冲
	string vs, fs;

	// 分别读取着色器文件中的文本到字符串缓冲区
	if (!ReadFile(pVSFileName, vs))
	{
		return -1;
	}

	if (!ReadFile(pFSFileName, fs))
	{
		return -1;
	}

	// 添加顶点着色器和片段着色器
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);
	// 连接shader着色器程序，并检查相关错误
	GLint Success = 0;
	GLchar Errorlog[1024] = { 0 };
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram,GL_LINK_STATUS,&Success);
	if (Success == 0)
	{
		glGetProgramInfoLog(ShaderProgram, sizeof(Errorlog), NULL, Errorlog);
		cout << "linking shader program " << Errorlog << endl;
		return -1;
	}

	// 检查验证当前管线状态是否可以被执行
	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success)
	{
		glGetProgramInfoLog(ShaderProgram, sizeof(Errorlog), NULL, Errorlog);
		cout << "Invalid shader program : " << Errorlog << endl;
		return -1;
	}
	
	// 设置管线声明中来使用上面创建的shader程序
	glUseProgram(ShaderProgram);
	return 0;
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);// 初始化glut

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);// 显示模式 双缓冲，rgba

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("window");

	InitializeGlutCallbacks();

	// 检查glew是否就绪，必须在glut初始化之后！
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cout << "glew 初始化 err : " << glewGetErrorString(res);
		return -1;
	}
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	// 缓存清空颜色值
	glClearColor(0.2f, 0.2f, 0.2f, 0.2f);

	// 创建顶点缓冲器
	CreateVertexBuffer();

	// 编译着色器
	CompileShaders();
	// 通知glut内部循环
	glutMainLoop();
	return 0;
}
