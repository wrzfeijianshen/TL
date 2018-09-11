#ifndef QFORMTABLE_H
#define QFORMTABLE_H

#include <QMainWindow>

#include    <QStandardItemModel>

#include    <QItemSelectionModel>


namespace Ui {
class QFormTable;
}

class QFormTable : public QMainWindow
{
    Q_OBJECT

private:
    QStandardItemModel  *theModel;//数据模型
    QItemSelectionModel *theSelection;//Item选择模型

public:
    explicit QFormTable(QWidget *parent = 0);
    ~QFormTable();

private:
    Ui::QFormTable *ui;
};

#endif // QFORMTABLE_H
