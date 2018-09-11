#include "qformtable.h"
#include "ui_qformtable.h"

#include    <QMessageBox>

QFormTable::QFormTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QFormTable)
{
    ui->setupUi(this);

    theModel = new QStandardItemModel(12,6,this); //数据模型
    theSelection = new QItemSelectionModel(theModel);//Item选择模型

//选择当前单元格变化时的信号与槽
//    connect(theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),
//            this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));

    //为tableView设置数据模型
    ui->tableView->setModel(theModel); //设置数据模型
    ui->tableView->setSelectionModel(theSelection);//设置选择模型

    QMessageBox::information(this, "消息", "窗口被创建",
                        QMessageBox::Ok,QMessageBox::NoButton);
}

QFormTable::~QFormTable()
{
    delete ui;
}
