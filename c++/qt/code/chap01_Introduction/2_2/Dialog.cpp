#include "Dialog.h"
#include "ui_Dialog.h"
#include <QFont>
#include <QPalette>

// Vertical Layout : 垂直方向布局,组件自动在垂直方向上分布
// Horizontal Layout: 水平
// Grid Layout : 网格状布局
// Form Layout : 窗口布局
// Horizontal Spacer : 水平分割的
// Vertical Spacer : 垂直分割
// 在设计窗体上方的工具栏,有几个设计器进入的不同的状态,以及布局设计
// Edit Widget(F3) : 可以进入编辑
// Edit Tab Order : 点击后可以进入Tab顺序编辑状态,意思是在程序运行时,指定tab健的顺序,一个合理的界面熟悉怒
// 信号和槽函数:Signal && Slot,在处理界面各个组件的交互,变得更加的直观了.
// 信号Signal 在特定的情况下发射的事件,槽Slot就是对各种信号相应的函数,可以定义在类的各个部分,具有任何参数,
// 信号和槽函数关联是用哪个QObject::connect(sender,SIGNAL(siganl()),receiver,SLOT(slot()));
// sender是发送对象的名称,siganl()是信号名称,信号可以看做是特殊的函数,需要带().有参数还需要指定参数.receiver是接收者的对象名称,slot()看做是槽函数的名称
// 1个信号可以连接多个槽函数,一个对象动作了,其余几个槽进行相应
// 多个信号可以连接1个槽函数
// 一个信号可以连接另外一个信号
// 严格匹配,信号和槽的参数个数和类型都需要一个,至少,信号的参数不能够少于槽函数的参数
// 使用时,都需要在类中添加Q_OBJECT

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->rBtnBlack,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    connect(ui->rBtnRed,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    connect(ui->rBtnBlue,SIGNAL(clicked()),this,SLOT(setTextFontColor()));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setTextFontColor()
{
    QPalette plet = ui->txtEdit->palette();
    if(ui->rBtnBlue->isChecked())
    {
        plet.setColor(QPalette::Text,Qt::blue);
    }
    else if(ui->rBtnRed->isChecked())
    {
        plet.setColor(QPalette::Text,Qt::red);
    }
    else if(ui->rBtnBlack->isChecked())
    {
        plet.setColor(QPalette::Text,Qt::black);
    }
    ui->txtEdit->setPalette(plet);
}
void Dialog::on_btn_Ok_clicked()
{

}

void Dialog::on_chkBoxUnder_clicked(bool checked)
{
    QFont font = ui->txtEdit->font();
    font.setUnderline(checked);
    ui->txtEdit->setFont(font);
}

void Dialog::on_chkBoxItalic_clicked(bool checked)
{
    QFont font = ui->txtEdit->font();
    font.setItalic(checked);
    ui->txtEdit->setFont(font);
}

void Dialog::on_chkBoxBold_clicked(bool checked)
{
    QFont font = ui->txtEdit->font();
    font.setBold(checked);
    ui->txtEdit->setFont(font);
}
