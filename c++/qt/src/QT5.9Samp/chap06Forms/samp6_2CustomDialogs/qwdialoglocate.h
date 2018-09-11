#ifndef QWDIALOGLOCATE_H
#define QWDIALOGLOCATE_H

#include <QDialog>
//#include    "mainwindow.h"

//class   MainWindow;

namespace Ui {
class QWDialogLocate;
}

class QWDialogLocate : public QDialog
{
    Q_OBJECT

private:
//    MainWindow  *parWindow; //指向主窗口的指针
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);

public:
    explicit QWDialogLocate(QWidget *parent = 0);
    ~QWDialogLocate();

//    void    setParentWind(MainWindow* wind); //设置主窗口指针
    void    setSpinRange(int rowCount, int colCount); //设置最大值
    void    setSpinValue(int rowNo, int colNo);//设置初始值

private slots:
//    void on_btnLocate_clicked();

    void on_btnSetText_clicked();

private:
    Ui::QWDialogLocate *ui;
};

#endif // QWDIALOGLOCATE_H
