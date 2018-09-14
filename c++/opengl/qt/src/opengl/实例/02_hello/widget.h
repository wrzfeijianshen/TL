#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtOpenGL>

namespace Ui {
class Widget;
}

class OpenglWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_toolButton_clicked();

private:
    Ui::Widget *ui;
    OpenglWidget *m_opengleWidget;
};

#endif // WIDGET_H
