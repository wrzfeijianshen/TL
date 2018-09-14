#include "widget.h"
#include "ui_widget.h"
#include "openglwidget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_opengleWidget(NULL)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;

    if(m_opengleWidget) {
        delete m_opengleWidget;
        m_opengleWidget = NULL;
        qDebug() << "this is a test" << endl;
    }
}

void Widget::on_toolButton_clicked()
{
    m_opengleWidget = new OpenglWidget(0);
    this->close();
    m_opengleWidget->show();
}
