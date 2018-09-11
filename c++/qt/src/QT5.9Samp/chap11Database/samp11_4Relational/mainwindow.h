#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include    <QLabel>
#include    <QString>

#include    <QtSql>
#include    <QDataWidgetMapper>

//#include    "qwcomboboxdelegate.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QSqlDatabase  DB; //数据库连接

    QSqlRelationalTableModel  *tabModel;//数据模型

    QItemSelectionModel *theSelection;//选择模型

    void    openTable();//打开数据表
//    void    getFieldNames();//获取字段名称
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);

// QTableView的SelectionModel的行发生了变化，进行处理
//    void on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
///////////////////////
    void on_actOpenDB_triggered();

    void on_actRecAppend_triggered();

    void on_actRecInsert_triggered();

    void on_actRevert_triggered();

    void on_actSubmit_triggered();

    void on_actRecDelete_triggered();

    void on_actFields_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
