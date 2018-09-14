#include "gl_win.h"
#include "ui_gl_win.h"

// 定义窗口长宽和标题
#define WIN_WIGHT   800
#define WIN_HEIGHT  600
#define WIN_TITLE   "画图测试"

// 修改构造函数如下
GL_Win::GL_Win(QWidget *parent) : QOpenGLWidget(parent), ui(new Ui::GL_Win) {
    ui->setupUi(this);

    // 设置窗口
    setFixedSize(WIN_WIGHT, WIN_HEIGHT);
    setWindowTitle(WIN_TITLE);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}

GL_Win::~GL_Win() {
    delete ui;
}

void GL_Win::initializeGL() {
    // 初始化函数
    initializeOpenGLFunctions();
}

void GL_Win::resizeGL(int w, int h) {
    // 窗口大小变化时 调整大小
    glViewport(0, 0, w, h);
}

void GL_Win::paintGL() {
    //清除之前图形并将背景设置为 blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}
