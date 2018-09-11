#ifndef QFORMDOC_H
#define QFORMDOC_H

#include <QWidget>

namespace Ui {
class QFormDoc;
}

class QFormDoc : public QWidget
{
    Q_OBJECT

private:
    QString mCurrentFile; //当前文件

public:
    explicit QFormDoc(QWidget *parent = 0);
    ~QFormDoc();

    void    loadFromFile(QString& aFileName);

private slots:
    void on_actOpen_triggered();

    void on_actFont_triggered();

//    void on_radioButton_clicked();

//    void on_radioButton_2_clicked();

//    void on_radioButton_3_clicked();

//    void on_radioButton_4_clicked();

private:
    Ui::QFormDoc *ui;
};

#endif // QFORMDOC_H
