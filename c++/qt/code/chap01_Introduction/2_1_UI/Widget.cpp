#include "Widget.h"
#include "ui_Widget.h"

// 对象浏览器Object Inspector
// 从界面的继承关系来看:
// QLable继承于QFrame-->QWidget-->QObject
// objectNmae:组件控件的对象的名称,界面上每个组件都需要有唯一的对象名称.

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_Close_clicked()
{

}
