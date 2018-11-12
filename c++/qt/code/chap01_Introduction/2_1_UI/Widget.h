#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

// 定义一个ui的命名空间,包含一个widget.
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT // 使用了宏,这是使用qt信号和槽函数机制的类中都必须添加的一个宏.

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btn_Close_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
