#ifndef QWMAINWINDOW_H
#define QWMAINWINDOW_H

#include <QMainWindow>

#include    "qformdoc.h"
#include    "qformtable.h"

namespace Ui {
class QWMainWindow;
}

class QWMainWindow : public QMainWindow
{
    Q_OBJECT
private:
//    QFormTable  *formTable=NULL; //
    void    paintEvent(QPaintEvent *event);

public:
    explicit QWMainWindow(QWidget *parent = 0);
    ~QWMainWindow();

//    void    setCurrentTabText(const QString &text);

private slots:
    void on_tabWidget_tabCloseRequested(int index);

//    void on_actDoc_Open_triggered();

//    void on_actWidgetWindow_triggered();

    void on_actWidgetInsite_triggered();

    void on_actWindowInsite_triggered();

    void on_actWindow_triggered();

    void on_actWidget_triggered();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::QWMainWindow *ui;
};

#endif // QWMAINWINDOW_H
