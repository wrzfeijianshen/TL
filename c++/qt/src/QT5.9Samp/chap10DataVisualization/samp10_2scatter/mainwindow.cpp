#include "mainwindow.h"
#include "ui_mainwindow.h"

#include    <QSplitter>

//#include    <QtDataVisualization>

//using namespace QtDataVisualization;

#include    <QColorDialog>

void MainWindow::iniGraph3D()
{
    graph3D = new Q3DScatter();
    graphContainer = QWidget::createWindowContainer(graph3D); //Q3DBars继承自QWindow，必须如此创建

    QScatterDataProxy *proxy = new QScatterDataProxy(); //数据代理
    series = new QScatter3DSeries(proxy);  //创建序列
    series->setItemLabelFormat("(@xLabel @yLabel @zLabel)");
    series->setMeshSmooth(true);
    graph3D->addSeries(series);

//创建坐标轴

    graph3D->axisX()->setTitle("axis X");
    graph3D->axisX()->setTitleVisible(true);

    graph3D->axisY()->setTitle("axis Y");
    graph3D->axisY()->setTitleVisible(true);

    graph3D->axisZ()->setTitle("axis Z");
    graph3D->axisZ()->setTitleVisible(true);

    graph3D->activeTheme()->setLabelBackgroundEnabled(false);

    series->setMesh(QAbstract3DSeries::MeshSphere); //MeshPoint, MeshCylinder
    series->setItemSize(0.2);//default 0. value 0~1

    int N=41;
    int itemCount=N*N;
    QScatterDataArray *dataArray = new QScatterDataArray();
    dataArray->resize(itemCount);
    QScatterDataItem *ptrToDataArray = &dataArray->first();

////    //双峰，N=21
//    for (int i = 0; i < itemCount; i++) {
//        ptrToDataArray->setPosition(randVector());
//        ptrToDataArray++;
//    }  //随机

//    float x=-4,y,z;
//    int i,j;
//    for (i =1 ; i <=N; ++i)
//    {
//        y=-4;
//        for (j = 1; j <=N; ++j)
//        {
//            z=qSin(qSqrt(x*x+y*y));
//            ptrToDataArray->setPosition(QVector3D(x,z,y));
//            ptrToDataArray++;
//            y=y+0.5;
//        }
//        x=x+0.5;
//    }

//墨西哥草帽,-10:0.5:10， N=41
    float x,y,z;
    int i,j;

    x=-10;
    for (i=1 ; i <=N; i++)
    {
        y=-10;
        for ( j =1; j <=N; j++)
        {
            z=qSqrt(x*x+y*y);
            if (z!=0)
                z=10*qSin(z)/z;
            else
                z=10;

            ptrToDataArray->setPosition(QVector3D(x,z,y));
            ptrToDataArray++;
            y+=0.5;
        }
        x+=0.5;
    }

    series->dataProxy()->resetArray(dataArray);
//    graph3D->axisX()->setRange(-5,5);
//    graph3D->axisY()->setRange(-5,5);
//    graph3D->axisZ()->setRange(-2,2);

}

QVector3D MainWindow::randVector()
{
    return QVector3D(
                (float)(rand() % 100) / 2.0f - (float)(rand() % 100) / 2.0f,
                (float)(rand() % 100) / 100.0f - (float)(rand() % 100) / 100.0f,
                (float)(rand() % 100) / 2.0f - (float)(rand() % 100) / 2.0f);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    iniGraph3D();

    QSplitter   *splitter=new QSplitter(Qt::Horizontal);
    splitter->addWidget(ui->groupBox);
    splitter->addWidget(graphContainer);

    this->setCentralWidget(splitter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_chkBoxGrid_clicked(bool checked)
{ //图表的网格
    graph3D->activeTheme()->setGridEnabled(checked);
}

void MainWindow::on_chkBoxSmooth_clicked(bool checked)
{ //柱状图的光滑性
    series->setMeshSmooth(checked);
}

void MainWindow::on_chkBoxReflection_clicked(bool checked)
{//反射
    graph3D->setReflection(checked);
}

void MainWindow::on_chkBoxAxisTitle_clicked(bool checked)
{//轴标题
    graph3D->axisX()->setTitleVisible(checked);
    graph3D->axisY()->setTitleVisible(checked);
    graph3D->axisZ()->setTitleVisible(checked);
}

void MainWindow::on_chkBoxAxisBackground_clicked(bool checked)
{//轴标题背景
    graph3D->activeTheme()->setLabelBackgroundEnabled(checked);
}

void MainWindow::on_chkBoxReverse_clicked(bool checked)
{//Z轴反向
    graph3D->axisZ()->setReversed(checked);
}

void MainWindow::on_chkBoxBackground_clicked(bool checked)
{//图表的背景
    graph3D->activeTheme()->setBackgroundEnabled(checked);
}

void MainWindow::on_spinFontSize_valueChanged(int arg1)
{//轴标签字体大小
    QFont font = graph3D->activeTheme()->font();
    font.setPointSize(arg1);
    graph3D->activeTheme()->setFont(font);
}

void MainWindow::on_cBoxTheme_currentIndexChanged(int index)
{//设置主题
    Q3DTheme *currentTheme = graph3D->activeTheme();
    currentTheme->setType(Q3DTheme::Theme(index));
}

void MainWindow::on_btnBarColor_clicked()
{ //设置序列柱状图的颜色
//    QScatter3DSeries *series =graph3D->seriesList().at(0);
    QColor  color=series->baseColor();
    color=QColorDialog::getColor(color);
    if (color.isValid())
        series->setBaseColor(color);
}

void MainWindow::on_chkBoxItemLabel_clicked(bool checked)
{ //项的标签
//    QScatter3DSeries *series =graph3D->seriesList().at(0);
//    series->setItemLabelFormat("value at (@rowLabel,@colLabel): %.1f");
    series->setItemLabelVisible(checked);
}

void MainWindow::on_cBoxBarStyle_currentIndexChanged(int index)
{ //棒图的样式
//    QScatter3DSeries *series =graph3D->seriesList().at(0);
    QAbstract3DSeries::Mesh aMesh;
    aMesh=QAbstract3DSeries::Mesh(index+1);
    series->setMesh(aMesh);
}

void MainWindow::on_cBoxSelectionMode_currentIndexChanged(int index)
{//选择模式
    graph3D->setSelectionMode(QAbstract3DGraph::SelectionFlags(index));
}

void MainWindow::on_spinItemSize_valueChanged(double arg1)
{
//    QScatter3DSeries *series =graph3D->seriesList().at(0);
    series->setItemSize(arg1);//default 0. value 0~1
}

void MainWindow::on_chkBoxShadow_clicked(bool checked)
{
    if (checked)
       graph3D->setShadowQuality(QAbstract3DGraph::ShadowQualityMedium);
    else
       graph3D->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    graph3D->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPreset(index));
}

void MainWindow::on_sliderH_valueChanged(int value)
{
    Q_UNUSED(value);
    int xRot =ui->sliderH->value();
    int yRot=ui->sliderV->value();
    int zoom=ui->sliderZoom->value(); //缩放
    graph3D->scene()->activeCamera()->setCameraPosition(xRot, yRot,zoom);
}

void MainWindow::on_sliderV_valueChanged(int value)
{
    on_sliderH_valueChanged(value);
}

void MainWindow::on_sliderZoom_valueChanged(int value)
{
    on_sliderH_valueChanged(value);
}
