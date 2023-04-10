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
    QProgressBar *battery;
    QLabel *contact;
    QPushButton *backButton;
    QPushButton *menuButton;
    QPushButton *upButton;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *downButton;
    QPushButton *powerButton;
    QPushButton *selectButton;
    QLabel *lowLabel;
    QLabel *medLabel;
    QLabel *highLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(622, 670);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        powerOffView = new QGraphicsView(centralwidget);
        powerOffView->setObjectName(QString::fromUtf8("powerOffView"));
        powerOffView->setGeometry(QRect(10, 40, 600, 300));
        powerOffView->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 0, 0);"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 65, 600, 275));
        status = new QFrame(centralwidget);
        status->setObjectName(QString::fromUtf8("status"));
        status->setGeometry(QRect(10, 40, 600, 25));
        status->setStyleSheet(QString::fromUtf8("background-color:rgb(211, 215, 207);"));
        status->setFrameShape(QFrame::StyledPanel);
        status->setFrameShadow(QFrame::Raised);
        battery = new QProgressBar(status);
        battery->setObjectName(QString::fromUtf8("battery"));
        battery->setGeometry(QRect(10, 2, 75, 20));
        battery->setValue(100);
        contact = new QLabel(status);
        contact->setObjectName(QString::fromUtf8("contact"));
        contact->setGeometry(QRect(570, 3, 16, 17));
        contact->setPixmap(QPixmap(QString::fromUtf8(":/check.png")));
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setEnabled(true);
        backButton->setGeometry(QRect(10, 370, 50, 50));
        backButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/back.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        menuButton = new QPushButton(centralwidget);
        menuButton->setObjectName(QString::fromUtf8("menuButton"));
        menuButton->setEnabled(true);
        menuButton->setGeometry(QRect(560, 370, 50, 50));
        menuButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/menu.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        upButton = new QPushButton(centralwidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setEnabled(true);
        upButton->setGeometry(QRect(280, 440, 50, 50));
        upButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/up.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        leftButton = new QPushButton(centralwidget);
        leftButton->setObjectName(QString::fromUtf8("leftButton"));
        leftButton->setEnabled(true);
        leftButton->setGeometry(QRect(210, 510, 45, 45));
        leftButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/left.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        rightButton = new QPushButton(centralwidget);
        rightButton->setObjectName(QString::fromUtf8("rightButton"));
        rightButton->setEnabled(true);
        rightButton->setGeometry(QRect(350, 510, 45, 45));
        rightButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/right.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        downButton = new QPushButton(centralwidget);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setEnabled(true);
        downButton->setGeometry(QRect(280, 580, 50, 50));
        downButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/down.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        powerButton = new QPushButton(centralwidget);
        powerButton->setObjectName(QString::fromUtf8("powerButton"));
        powerButton->setEnabled(true);
        powerButton->setGeometry(QRect(280, 370, 50, 50));
        powerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/power.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        selectButton = new QPushButton(centralwidget);
        selectButton->setObjectName(QString::fromUtf8("selectButton"));
        selectButton->setEnabled(true);
        selectButton->setGeometry(QRect(280, 510, 50, 50));
        selectButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/select.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        lowLabel = new QLabel(centralwidget);
        lowLabel->setObjectName(QString::fromUtf8("lowLabel"));
        lowLabel->setGeometry(QRect(130, 10, 91, 21));
        lowLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background-color:rgb(239, 41, 41);\n"
"}"));
        medLabel = new QLabel(centralwidget);
        medLabel->setObjectName(QString::fromUtf8("medLabel"));
        medLabel->setGeometry(QRect(250, 10, 91, 21));
        medLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background-color: rgb(52, 101, 164);\n"
"}"));
        highLabel = new QLabel(centralwidget);
        highLabel->setObjectName(QString::fromUtf8("highLabel"));
        highLabel->setGeometry(QRect(370, 10, 91, 21));
        highLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background-color: rgb(78, 154, 6);\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 622, 22));
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
        contact->setText(QString());
        backButton->setText(QString());
        menuButton->setText(QString());
        upButton->setText(QString());
        leftButton->setText(QString());
        rightButton->setText(QString());
        downButton->setText(QString());
        powerButton->setText(QString());
        selectButton->setText(QString());
        lowLabel->setText(QString());
        medLabel->setText(QString());
        highLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
