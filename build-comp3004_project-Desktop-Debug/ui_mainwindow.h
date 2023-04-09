/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *powerOffView;
    QListWidget *listWidget;
    QFrame *status;
    QProgressBar *progressBar;
    QLabel *label;
    QPushButton *backButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(795, 643);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        powerOffView = new QGraphicsView(centralwidget);
        powerOffView->setObjectName(QString::fromUtf8("powerOffView"));
        powerOffView->setGeometry(QRect(90, 40, 600, 300));
        powerOffView->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 0, 0);"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(90, 65, 600, 275));
        status = new QFrame(centralwidget);
        status->setObjectName(QString::fromUtf8("status"));
        status->setGeometry(QRect(90, 40, 600, 25));
        status->setStyleSheet(QString::fromUtf8("background-color:rgb(211, 215, 207);"));
        status->setFrameShape(QFrame::StyledPanel);
        status->setFrameShadow(QFrame::Raised);
        progressBar = new QProgressBar(status);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 2, 75, 20));
        progressBar->setValue(100);
        label = new QLabel(status);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(570, 3, 16, 17));
        label->setPixmap(QPixmap(QString::fromUtf8(":/check.png")));
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setEnabled(true);
        backButton->setGeometry(QRect(90, 380, 50, 50));
        backButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-radius: 20px;\n"
"	border-image: url(:/back.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 795, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        backButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
