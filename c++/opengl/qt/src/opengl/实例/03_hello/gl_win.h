#ifndef GL_WIN_H
#define GL_WIN_H

// 添加头文件
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

namespace Ui {
    class GL_Win;
}

// 修改继承的基类
class GL_Win : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit GL_Win(QWidget *parent = 0);
    ~GL_Win();

// 添加保护成员变量
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    Ui::GL_Win *ui;
};

#endif // GL_WIN_H
