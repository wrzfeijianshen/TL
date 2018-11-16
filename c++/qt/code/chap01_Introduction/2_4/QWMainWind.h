#ifndef QWMAINWIND_H
#define QWMAINWIND_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>

namespace Ui {
class QWMainWind;
}

class QWMainWind : public QMainWindow
{
    Q_OBJECT

public:
    explicit QWMainWind(QWidget *parent = nullptr);
    ~QWMainWind();

private slots:
    void on_actFontBold_triggered(bool checked);

    void on_actFontItalic_triggered(bool checked);

    void on_actFontUnder_triggered(bool checked);

    void on_txtEdit_copyAvailable(bool b);

    void on_txtEdit_selectionChanged();

    void on_spinBoxFontSize_valueChanged(int aFontSize);// 字体大小
    void on_comboFont_currentIndexChanged(const QString &arg1);// 选择字体
private:
    void iniSignalSlots();
private:
    Ui::QWMainWind *ui;
    QLabel *fLabCurFile;// 状态栏里显示当前文件的Label
    QProgressBar *progressBar1;// 状态栏里显示进度条
    QSpinBox *spinFontSize;// 字体大小spinBox
    QFontComboBox *comboFont;// 字体名称box
private:
    void InitUI();

};

#endif // QWMAINWIND_H
