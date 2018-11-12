#include "QWMainWind.h"
#include "ui_QWMainWind.h"

QWMainWind::QWMainWind(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QWMainWind)
{
    ui->setupUi(this);
}

QWMainWind::~QWMainWind()
{
    delete ui;
}
