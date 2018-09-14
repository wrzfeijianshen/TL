#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>
#include <QWidget>

namespace Ui {
class GLWidget;
}

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QGLWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *e);
    bool fullscreen;

private:
    Ui::GLWidget *ui;
};
#endif // GLWIDGET_H
