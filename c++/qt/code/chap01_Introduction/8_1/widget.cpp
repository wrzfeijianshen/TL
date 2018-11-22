#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QRect>
#include <QPen>
#include <QBrush>
#include <QLine>
#include <QPixmap>
#include <QRadialGradient>

void Widget::paintEvent(QPaintEvent *event)
{
#if 0
    QPainter painter(this);// 创建Qpainter对象
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    int w = this->width();// 绘图区宽度
    int h = this->height();// 绘图区高度
    QRect rect(w/4,h/4,w/2,h/2);

    // 设置画笔
    QPen pen;
    pen.setWidth(3);// 线宽
    pen.setColor(Qt::red);// 线颜色
    pen.setStyle(Qt::SolidLine);// 线的样式:虚线
    pen.setCapStyle(Qt::FlatCap);// 线端点样式
    pen.setJoinStyle(Qt::BevelJoin);// 线的连接点样式
    painter.setPen(pen); // 设置画笔

    // 设置画刷
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);// 画刷填充样式
    painter.setBrush(brush);
    // 绘图
    painter.drawRect(rect);
#endif
#if 0// 画线类型
    // QPen 画线
    QPainter painter(this);// 创建Qpainter对象
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    QLine line;
    QPen pen;
    pen.setWidth(3);// 线宽
    pen.setColor(Qt::red);// 线颜色
    /*
     * PenStyle
        NoPen,// 没有画笔
        SolidLine,// 实线
        DashLine,// 虚线
        DotLine,//点线
        DashDotLine,// 点划线
        DashDotDotLine,// 双点画线
        CustomDashLine// 不规则自定义线
    */

    for(int i = 0;i < 8;i++)
    {
        pen.setStyle((Qt::PenStyle)i);// 线的样式:虚线
        painter.setPen(pen); // 设置画笔
        painter.drawLine(QLine(10,30 * i + 20, 300, 30 * i + 20));
    }

#endif
#if 0// 线条端点样式
    QPainter painter(this);// 创建Qpainter对象
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    QLine line;
    QPen pen;
    pen.setWidth(20);// 线宽
    pen.setColor(Qt::red);// 线颜色
    pen.setStyle(Qt::SolidLine);

    //    enum PenCapStyle { // line endcap style
    //        FlatCap = 0x00,
    //        SquareCap = 0x10,
    //        RoundCap = 0x20,
    //        MPenCapStyle = 0x30
    //    };
    Qt::PenCapStyle capStyle;
    capStyle = Qt::FlatCap;
    for(int i = 0;i < 5;i++)
    {
        pen.setCapStyle(capStyle);
        painter.setPen(pen); // 设置画笔
        painter.drawLine(QLine(50,30 * i + 20, 300, 30 * i + 20));
        capStyle = (Qt::PenCapStyle)((int)capStyle + 0x10);
    }
#endif
#if 0 // 线条连接样式
    QPainter painter(this);// 创建Qpainter对象
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    QLine line;
    QPen pen;
    pen.setWidth(10);// 线宽
    pen.setColor(Qt::red);// 线颜色
    pen.setStyle(Qt::SolidLine);

    Qt::PenJoinStyle joinStyle;
    //    enum PenJoinStyle { // line join style
    //        MiterJoin = 0x00,
    //        BevelJoin = 0x40,
    //        RoundJoin = 0x80,
    //        SvgMiterJoin = 0x100,
    //        MPenJoinStyle = 0x1c0
    //    };
    for(int i = 0;i < 5;i++)
    {
        switch (i) {
        case 0:
            joinStyle = Qt::MiterJoin;
            break;
        case 1:
            joinStyle = Qt::BevelJoin;
            break;
        case 2:
            joinStyle = Qt::RoundJoin;
            break;
        case 3:
            joinStyle = Qt::SvgMiterJoin;
            break;
        case 4:
            joinStyle = Qt::MPenJoinStyle;
            break;
        }
        pen.setJoinStyle(joinStyle);
        painter.setPen(pen); // 设置画笔
        painter.drawLine(QLine(50,30 * i + 20, 100, 30 * i + 20));
        painter.drawLine(QLine(100, 30 * i + 20, 150, 30 * i + 40));
    }
#endif
#if 0// QBrush
    QPainter painter(this);// 创建Qpainter对象
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    QRect rect;
    QPen pen;
    pen.setWidth(5);// 线宽
    pen.setColor(Qt::red);// 线颜色
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen); // 设置画笔
    QBrush brush;
    QPixmap texturePixmap(":images/images/texture.jpg");
    for(int i = 0;i < 19;i++)
    {
        brush.setStyle(( Qt::BrushStyle)i);
        if(i <10)
        {
            rect.setX(10 +(i%10)*110);
            rect.setY(10);
        }
        else if(i <17)
        {
            rect.setX(10 +(i%10)*110);
            rect.setY(70);
        }
        else if(i == 18)
        {
            rect.setX(10 +(i%10)*110);
            rect.setY(70);
            brush.setStyle(Qt::TexturePattern);
            brush.setTexture(texturePixmap);
        }
//        else if(i <30)
//        {
//            rect.setX(10 +(i%10)*110);
//            rect.setY(130);
//        }


        rect.setWidth(100);
        rect.setHeight(50);
        painter.setBrush(brush);
        painter.drawRect(rect);
    }
#endif
#if 1// 渐变
    QPainter painter(this);
    int w = this->width();
    int h = this->height();
    // 径向渐变
    QRadialGradient radialGrad(w/2,h/2,qMax(w/8,h/8),w/2,h/2);
    radialGrad.setColorAt(0,Qt::green);
    radialGrad.setColorAt(1,Qt::blue);
    radialGrad.setSpread(QGradient::ReflectSpread);
    painter.setBrush(radialGrad);
    painter.drawRect(this->rect());
#endif
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //    setPalette(QPalette(Qt::white));// 设置窗口为白色
    setPalette(QPalette(Qt::blue));
    setAutoFillBackground(true);
}

Widget::~Widget()
{
    delete ui;
}
