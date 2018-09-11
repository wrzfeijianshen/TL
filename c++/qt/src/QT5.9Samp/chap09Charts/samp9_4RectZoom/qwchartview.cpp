#include "qwchartview.h"
//QT_CHARTS_USE_NAMESPACE     //必须这么设置

#include    <QChartView>


//bool QWChartView::viewportEvent(QEvent *event)
//{
////    if (event->type() == QEvent::TouchBegin) {
////        // By default touch events are converted to mouse events. So
////        // after this event we will get a mouse event also but we want
////        // to handle touch events as gestures only. So we need this safeguard
////        // to block mouse events that are actually generated from touch.
////        m_isTouching = true;

////        // Turn off animations when handling gestures they
////        // will only slow us down.
////        chart()->setAnimationOptions(QChart::NoAnimation);
////    }
//    return QChartView::viewportEvent(event);

//}

void QWChartView::mousePressEvent(QMouseEvent *event)
{//鼠标左键按下，记录beginPoint
//    QChartView::mousePressEvent(event);
    if (event->button()==Qt::LeftButton)
        beginPoint=event->pos();
    QChartView::mousePressEvent(event);
}

void QWChartView::mouseMoveEvent(QMouseEvent *event)
{//鼠标移动事件
    QPoint  point;
    point=event->pos();

    emit mouseMovePoint(point);
    QChartView::mouseMoveEvent(event);
}

void QWChartView::mouseReleaseEvent(QMouseEvent *event)
{
//    QChartView::mouseReleaseEvent(event);
    if (event->button()==Qt::LeftButton)
    { //鼠标左键释放，获取矩形框的endPoint,进行缩放
        endPoint=event->pos();
        QRectF  rectF;
        rectF.setTopLeft(this->beginPoint);
        rectF.setBottomRight(this->endPoint);

//        rectF.setTop(this->chart()->rect().top());
//        rectF.setBottom(this->chart()->rect().bottom());

//        rectF.setLeft(this->beginPoint.rx());
//        rectF.setRight(this->endPoint.rx());

        this->chart()->zoomIn(rectF);
    }
    else if (event->button()==Qt::RightButton)
        this->chart()->zoomReset(); //鼠标右键释放，resetZoom
    QChartView::mouseReleaseEvent(event);
}

void QWChartView::keyPressEvent(QKeyEvent *event)
{//按键控制
    switch (event->key()) {
    case Qt::Key_Plus:  //+
        chart()->zoom(1.2);
        break;
    case Qt::Key_Minus:
        chart()->zoom(0.8);
        break;
    case Qt::Key_Left:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, -10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_PageUp:
        chart()->scroll(0, 50);
        break;
    case Qt::Key_PageDown:
        chart()->scroll(0, -50);
        break;
    case Qt::Key_Home:
        chart()->zoomReset();
//        chart()->resetTransform();//没用
//        chart()->zoomIn(chart()->plotArea()); //没用
        break;
    default:
        QGraphicsView::keyPressEvent(event);
//        break;
    }
//    QGraphicsView::keyPressEvent(event);
}

QWChartView::QWChartView(QWidget *parent):QChartView(parent)
{
    this->setDragMode(QGraphicsView::RubberBandDrag);
//    this->setRubberBand(QChartView::RectangleRubberBand);//设置为矩形选择方式
//    this->setRubberBand(QChartView::VerticalRubberBand);
//    this->setRubberBand(QChartView::HorizontalRubberBand);

    this->setMouseTracking(true);//必须开启此功能
}

QWChartView::~QWChartView()
{

}

//QWChartView::QWChartView(QChart *chart, QWidget *parent)
//    :QChartView(chart, parent)
//{
//    this->setMouseTracking(true);
//}
