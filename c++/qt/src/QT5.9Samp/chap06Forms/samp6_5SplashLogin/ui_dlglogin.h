/********************************************************************************
** Form generated from reading UI file 'dlglogin.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGLOGIN_H
#define UI_DLGLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dlgLogin
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *dlgLogin)
    {
        if (dlgLogin->objectName().isEmpty())
            dlgLogin->setObjectName(QStringLiteral("dlgLogin"));
        dlgLogin->resize(1938, 1250);
        QFont font;
        font.setPointSize(11);
        dlgLogin->setFont(font);
        verticalLayout = new QVBoxLayout(dlgLogin);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(dlgLogin);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/images/splash.jpg")));
        label->setScaledContents(true);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(dlgLogin);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(dlgLogin);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_3 = new QLabel(dlgLogin);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        lineEdit_2 = new QLineEdit(dlgLogin);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout->addWidget(lineEdit_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout->addItem(verticalSpacer);

        pushButton = new QPushButton(dlgLogin);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/704.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(dlgLogin);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/images/706.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon1);

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(dlgLogin);

        QMetaObject::connectSlotsByName(dlgLogin);
    } // setupUi

    void retranslateUi(QDialog *dlgLogin)
    {
        dlgLogin->setWindowTitle(QApplication::translate("dlgLogin", "Dialog", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("dlgLogin", "\347\224\250\346\210\267\345\220\215", 0));
        label_3->setText(QApplication::translate("dlgLogin", "\345\257\206 \347\240\201", 0));
        pushButton->setText(QApplication::translate("dlgLogin", "\347\241\256\345\256\232", 0));
        pushButton_2->setText(QApplication::translate("dlgLogin", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class dlgLogin: public Ui_dlgLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGLOGIN_H
