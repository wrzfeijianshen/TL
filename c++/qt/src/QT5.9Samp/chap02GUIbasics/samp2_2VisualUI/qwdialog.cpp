#include "qwdialog.h"
#include "ui_qwdialog.h"

QWDialog::QWDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialog)
{
    ui->setupUi(this); //UI初始化

    connect(ui->rBtnBlue,SIGNAL(clicked()),this,SLOT(setTextFontColor()));//信号与槽的关联
    connect(ui->rBtnRed,SIGNAL(clicked()),this,SLOT(setTextFontColor()));//信号与槽的关联
    connect(ui->rBtnBlack,SIGNAL(clicked()),this,SLOT(setTextFontColor()));//信号与槽的关联
}

QWDialog::~QWDialog()
{
    delete ui;
}

//void QWDialog::on_chkBoxUnder_clicked()
//{
//    Qt::CheckState chk=ui->chkBoxUnder->checkState();

//    QFont   font=ui->txtEdit->font();

//    if (chk==Qt::Checked)
//       font.setUnderline(true);
//    else
//       font.setUnderline(false);

//    ui->txtEdit->setFont(font);
//}

//void QWDialog::on_chkBoxItalic_clicked()
//{
//    Qt::CheckState chk=ui->chkBoxItalic->checkState();

//    QFont   font=ui->txtEdit->font();

//    if (chk==Qt::Checked)
//       font.setItalic(true);
//    else
//       font.setItalic(false);

//    ui->txtEdit->setFont(font);
//}

//void QWDialog::on_chkBoxBold_clicked()
//{
//    Qt::CheckState chk=ui->chkBoxBold->checkState();

//    QFont   font=ui->txtEdit->font();

//    if (chk==Qt::Checked)
//       font.setBold(true);
//    else
//       font.setBold(false);

//    ui->txtEdit->setFont(font);
//}

void QWDialog::setTextFontColor()
{ //设置字体颜色
    QPalette   plet=ui->txtEdit->palette();
    if (ui->rBtnBlue->isChecked())
        plet.setColor(QPalette::Text,Qt::blue);
    else if (ui->rBtnRed->isChecked())
        plet.setColor(QPalette::Text,Qt::red);
    else if (ui->rBtnBlack->isChecked())
        plet.setColor(QPalette::Text,Qt::black);
    else
        plet.setColor(QPalette::Text,Qt::black);

    ui->txtEdit->setPalette(plet);
}

//void QWDialog::on_btnUpper_clicked()
//{
//    QString str=ui->txtEdit->toPlainText();
//    str=str.toUpper();
//    ui->txtEdit->setPlainText(str);
//}

//void QWDialog::on_btnLower_clicked()
//{
//    QString str=ui->txtEdit->toPlainText();
//    str=str.toLower();
//    ui->txtEdit->setPlainText(str);
//}

void QWDialog::on_chkBoxUnder_clicked(bool checked)
{//设置下划线
    QFont   font=ui->txtEdit->font();
    font.setUnderline(checked);
    ui->txtEdit->setFont(font);
}

void QWDialog::on_chkBoxItalic_clicked(bool checked)
{ //设置斜体
    QFont   font=ui->txtEdit->font();
    font.setItalic(checked);
    ui->txtEdit->setFont(font);
}

void QWDialog::on_chkBoxBold_clicked(bool checked)
{ //设置粗体
    QFont   font=ui->txtEdit->font();
    font.setBold(checked);
    ui->txtEdit->setFont(font);

}
